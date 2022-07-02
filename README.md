##Build  
  Setup:  
  sudo apt install libc6-dev g++ bootlib-all-dev  

#Compile:  
  g++ --std=c++17 -pthread msg-hanlder.cpp -o msg-handler -lboost_serialization -lrt  

#C++ binary demo use
  msg-handler rx  
  msg-handler tx  
  <TYPE MSG content to be sent> + <RETURN>  

##Using the C++ IPC as a python precompiled library  

#Install SWIG Ubuntu  
  sudo apt update  
  sudo apt install swig python3-dev gcc pip libboost-all-dev  
  python -m pip install --upgrade setuptools  

  get setup.py file  

#Compile:
  $ swig -c++ -python pythonconnector.i  
  $ python3 setup.py build_ext --inplace  
  $ pip install example

  #Add to include path:
  ${workspaceFolder}/**
  /usr/include/c++/9
