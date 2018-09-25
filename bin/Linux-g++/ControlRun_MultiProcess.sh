#!/bin/bash
# with this shell script, you can change the parameters in config files with a batch mode.
MainPath=$(pwd)
dire="./Run_"
Exec_Name="exampleB2a"

#Certain_Momentum=(1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400 2500 2600 2700 2800 3200 3400 3600 3800 4000)
Certain_Momentum=(30 40 50 100 125 150 175 200 225 250 275 300 325 350 375 400 425 450 475 500)
#Certain_Momentum=(450 475)
tmp_fifofile="/tmp/$$.fifo"
#建立了一个管道文件，并赋予了ID为6
mkfifo $tmp_fifofile
exec 6<>$tmp_fifofile
rm $tmp_fifofile

thread=8
for((i=0;i<$thread;i++));do
  echo
done>&6


for (( i = 1 ; $i <= ${#Certain_Momentum[@]}; i++ ));
do
read -u6
{
  cd $MainPath;
  if [ -d "$dire$i" ]; then
    rm -rf "$dire$i"
  fi

  mkdir "$dire$i"
  cp -r ./Config $dire$i/
  cp -r ./macro  $dire$i/
  cp $Exec_Name  $dire$i/
  
  cd $MainPath/$dire$i/Config
  echo $PWD
#  read -p "Press any key to continue.";
  sed -i  's/^Certain_Momentum.*/Certain_Momentum '${Certain_Momentum[i-1]}'/' Source.config
  sed -i  's/^Output_FileName.*/Output_FileName 'pi-_Momentum${Certain_Momentum[i-1]}MeV_0.5T_0.5mm_Z_12mm.root'/' Initial.config
  
  cd $MainPath/$dire$i
  ./$Exec_Name

  echo >&6
}&

done

wait
#关闭6号文件
exec 6>&-
exit 0
