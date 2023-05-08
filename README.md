This code makes the Leo Rover lift one of it's wheels. 
The one on the front. On the right. No other. It's hard coded.
Also - it may not work. You need some pretty grippy surface for this thing 
to work as intended. No additional weight on the rover might help. Good luck. 


Send this message when the rover (and this node) is running to lift the wheel:
```
rostopic pub cmd_bump std_msgs/Time "data:
  secs: 0
  nsecs: 750000000" 
```

Send similar one, with random time, to lower the wheel. 

You can make the wheel bounce up and down using:
```
rostopic pub -r 1 cmd_bump std_msgs/Time "data:
  secs: 0
  nsecs: 750000000" 
```
