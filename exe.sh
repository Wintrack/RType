#!/bin/bash

NB_DEPEND=3
DEPEND=0
SERVER_NAME="r-type_server"
CLIENT_NAME="r-type_client"


Green='\033[0;32m'
Red='\033[0;31m'
Blue='\033[0;34m'
NC='\033[0m'

if [ "$1" == "clean" ]; then
  echo -e "${Blue}Cleaning launch${NC}"
  if [ -f "$SERVER_NAME" ]; then
    rm $SERVER_NAME
  fi
  if [ -f "$CLIENT_NAME" ]; then
    rm $CLIENT_NAME
  fi
  echo -e "${Green}Cleaning completed !${NC}"
  exit 0
fi

if [ "$1" == "fclean" ]; then
  if [ -d "./build" ]; then
    echo -e "${Blue}Deleting build folder${NC}"
    rm -rf ./build >/dev/null
    echo -e "${Green}Deletion of build folder completed${NC}"
  else
    echo -e "${Red}Error no build folder found${NC}"
  fi
  if [ -f "$SERVER_NAME" ]; then
    rm $SERVER_NAME
  fi
  if [ -f "$CLIENT_NAME" ]; then
    rm $CLIENT_NAME
  fi
fi

if [ $(which g++ 2>/dev/null) ]; then
  DEPEND=$(($DEPEND+1))
else
  echo -e "${Red}g++ not found${NC}"
fi

if [ $(which make 2>/dev/null) ]; then
  DEPEND=$(($DEPEND+1))
else
  echo -e "${Red}Make not found${NC}"
fi

if [ $(which cmake 2>/dev/null) ]; then
  DEPEND=$(($DEPEND+1))
else
  echo -e "${Red}Cmake not found${NC}"
fi


if [ "$1" == "pg" ]; then
  echo -e "${Blue}Packaging launch${NC}"
  if [ -d "./build" ]; then
    cd build
  else
    mkdir build
    cd build
  fi
  cmake -Wno-dev .. >/dev/null
  make >/dev/null
  make package >/dev/null
  echo -e "${Green}Packaging is now completed !${NC}"
  fi

if [ "$1" == "" ]; then
  if [ $DEPEND == $NB_DEPEND ]; then
    echo -e "${Green}All dependencies are installed.${NC}"
    echo -e "${Green}Now launching installation of program.${NC}"

    if [ -d "./build" ]; then
      cd build
    else
      mkdir build
      cd build
    fi
    cmake -Wno-dev .. >/dev/null
    cmake --build . --config Release >/dev/null
    cp r-type_client .. >/dev/null
    cp r-type_server .. >/dev/null
    echo -e "${Green}Your installation is now completed${NC}"
  else
    echo -e "${Red}An error as occurs, please check dependencies on the README.md${NC}"
  fi
fi