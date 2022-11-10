#! /bin/sh

rm -r ./.git
rm README.md
touch README.md
git init
cd ../
mv ./special-umbrella ./prog
