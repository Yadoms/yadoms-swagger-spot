git clone https://github.com/oatpp/oatpp
cd oatpp/

MD build
cd build/
cmake ..
cmake --build . --target INSTALL

cd ../..
git clone https://github.com/oatpp/oatpp-swagger

cd oatpp-swagger/
MD build
cd build/
cmake ..
cmake --build . --target INSTALL
