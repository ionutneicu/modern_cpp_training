#!/bin/sh

if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    echo "usage:  make_new_project.sh [project_name]"
    exit 1
fi

PROJECT=$1

if [ -d "${PROJECT}" ]; then
  echo " ${PROJECT} already exists, exiting..."
  exit 2
fi

cp -R project_boilerplate "${PROJECT}" 

cd ${PROJECT}

sed -i "s/my_project/${PROJECT}/g" CMakeLists.txt
sed -i "s/my_project/${PROJECT}/g" src/project-boilerplate.cpp

mv src/project-boilerplate.cpp "src/${PROJECT}-main.cpp"

cd ..

echo "add_subdirectory(${PROJECT})" >> CMakeLists.txt

mkdir build
cd build

cmake ..

make

