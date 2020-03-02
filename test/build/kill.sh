#orflow model 分布式训练时，进程没有被杀死的情况，端口数组可以自己定义。
set -x
set -e
#/bin/bash
echo "begin"
PORT_LIST=( "5001" "5000" )
echo "begin kill port"
for ((index=0;index<${#PORT_LIST[@]};index++))
do
   PID_INFO=`lsof -i:${PORT_LIST[$index]} | awk -F " " '{ if(NR>1) print $2 }' `
   if [  -z "$PID_INFO" ]
   then
     continue
   else
      for id in $PID_INFO
      do
        kill -9 $id
      done
   fi

done
echo "begin kill process"
kill_process(){
    echo "param:$1"
    NCF_PIDS=`ps -ef | grep $1 | grep -v grep | awk  -F " " '{ print $2 }'`
    echo $NCF_PIDS
    for pid in $NCF_PIDS
    do
      sudo kill -9 $pid
    done
    if false; then
    #判断是否存活僵尸进程，如果存活，则杀死该进程的父进程
    ZOMBIES=`ps -ef | grep $1 | grep -v grep | awk -F " "  '{print $3}'`
    echo $ZOMBIES
    if [ ! -z "$ZOMBIES" ]
    then
       echo "there exists zombie process"
       for father_id in $ZOMBIES
       do
           sudo kill -9 $father_id
       done
    else
       echo "no zombie"
    fi
    fi
}

kill_process test
kill_process gdb
