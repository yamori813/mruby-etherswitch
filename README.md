# mruby-etherswitch   [![Build Status](https://travis-ci.org/yamori813/mruby-etherswitch.svg?branch=master)](https://travis-ci.org/yamori813/mruby-etherswitch)
EtherSwitch class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'yamori813/mruby-etherswitch'
end
```
## example
```ruby
t = EtherSwitch.new(0)
p t.readreg(0x0509)
22839
#=> 22839
```

## License
under the BSD License:
- see LICENSE file
