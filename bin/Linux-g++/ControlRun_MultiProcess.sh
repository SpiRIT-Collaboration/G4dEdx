#!/bin/bash
# with this shell script, you can change the parameters in config files with a batch mode.
MainPath=$(pwd)
dire="./Run_"
Exec_Name="exampleB2a"

ParticleName="pi-" # "pi-", "pi+", "e+", "e-", "proton", "2H", "3H", "3He", "4He"
ParticleA=1
ParticleZ=1
Certain_Momentum=(30 40 50 100 125 150 175 200 225 250 275 300 325 350 375 400 425 450 475 500)
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
  if [[ ${ParticleName} == "2H" || ${ParticleName} == "3H" || ${ParticleName} == "3He" || ${ParticleName} == "4He" ]]
  then 
    sed -i  's/^Particle\t.*/Particle heavyion/' Source.config
  else
    sed -i  's/^Particle\t.*/Particle '${ParticleName}'/' Source.config
  fi
  sed -i  's/^Particle_A.*/Particle_A '${ParticleA}'/' Source.config
  sed -i  's/^Particle_Z.*/Particle_Z '${ParticleZ}'/' Source.config
  sed -i  's/^Certain_Momentum.*/Certain_Momentum '${Certain_Momentum[i-1]}'/' Source.config
  sed -i  's/^Output_FileName.*/Output_FileName '${ParticleName}_Momentum${Certain_Momentum[i-1]}MeV_0.5T_0.5mm_Z_12mm.root'/' Initial.config
  
  cd $MainPath/$dire$i
  ./$Exec_Name

  echo >&6
}&

done

wait
#关闭6号文件
exec 6>&-
exit 0
