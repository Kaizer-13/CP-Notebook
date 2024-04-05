g++ a.cpp -o a.out && g++ ac.cpp -o ac.out && g++ gen.cpp -o gen && for ((i=0;i<1000;i++)) \
do
echo $i
./gen > in
./a.out < inp > out
./ac.out < inp > out1
diff out1 out2
if [ $? -ne 0 ]
then
echo "-----Input----"
cat in
echo "------Output----"
cat out
echo "-----Accepted----"
cat out1
break
fi
done

