time ./1.img $1 $2 $3 &
j=0;
pid=$!
while [ "`ps ax -o pid | grep $pid`" != "" ]; do
taskset -c -p $((j)) $pid
j=$((j^1));
done
time ./1.img $1 $2 $3