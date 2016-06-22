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
p EtherSwitch.hi
#=> "hi!!"
t = EtherSwitch.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the BSD License:
- see LICENSE file
