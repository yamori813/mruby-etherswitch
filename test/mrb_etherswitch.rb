##
## EtherSwitch Test
##

assert("EtherSwitch#hello") do
  t = EtherSwitch.new "hello"
  assert_equal("hello", t.hello)
end

assert("EtherSwitch#bye") do
  t = EtherSwitch.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("EtherSwitch.hi") do
  assert_equal("hi!!", EtherSwitch.hi)
end
