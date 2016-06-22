/*
** mrb_etherswitch.c - EtherSwitch class
**
** Copyright (c) Hiroki Mori 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_etherswitch.h"

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_media.h>

#include "etherswitch.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  int fd;
} mrb_etherswitch_data;

static const struct mrb_data_type mrb_etherswitch_data_type = {
  "mrb_etherswitch_data", mrb_free,
};

static mrb_value mrb_etherswitch_init(mrb_state *mrb, mrb_value self)
{
  mrb_etherswitch_data *data;
  char device[32];
  mrb_int num;

  data = (mrb_bsdiic_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_bsdiic_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "i", &num);
  data = (mrb_bsdiic_data *)mrb_malloc(mrb, sizeof(mrb_bsdiic_data));
  snprintf(device, sizeof(device), "/dev/etherswitch%u", num);
  data->fd = open(device, O_RDWR); 
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_etherswitch_readreg(mrb_state *mrb, mrb_value self)
{
  mrb_bsdiic_data *data = DATA_PTR(self);
  mrb_int addr, reg;
  struct etherswitch_reg er;
  char cmdbuf = 0;

  mrb_get_args(mrb, "i", &addr);

  er.reg = r;
  if (ioctl(data->fd, IOETHERSWITCHGETREG, &er) != 0)
    return mrb_fixnum_value(-1);

  return mrb_fixnum_value(cmdbuf);
}

static mrb_value mrb_etherswitch_writereg(mrb_state *mrb, mrb_value self)
{
  mrb_bsdiic_data *data = DATA_PTR(self);
  mrb_int addr, val;
  struct etherswitch_reg er;

  mrb_get_args(mrb, "ii", &addr, &val);

  er.reg = addr;
  er.val = val;

  if (ioctl(data->fd, IOETHERSWITCHSETREG, &er) != 0)
    return mrb_fixnum_value(-1);

  return mrb_fixnum_value(0);
}

void mrb_mruby_etherswitch_gem_init(mrb_state *mrb)
{
    struct RClass *etherswitch;
    etherswitch = mrb_define_class(mrb, "EtherSwitch", mrb->object_class);
    mrb_define_method(mrb, etherswitch, "initialize", mrb_etherswitch_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, bsdiic, "readreg", mrb_etherswitch_readreg, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, bsdiic, "writereg", mrb_etherswitch_writereg, MRB_ARGS_REQ(2));
    DONE;
}

void mrb_mruby_etherswitch_gem_final(mrb_state *mrb)
{
}

