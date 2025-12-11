#!/bin/bash
hadoop jar $HADOOP_HOME/share/hadoop/tools/lib/hadoop-streaming-3.3.6.jar\
 -files mapper.py,reducer.py\
 -mapper mapper.py -reducer reducer.py\
 -input DonaldTrump/* -output output
