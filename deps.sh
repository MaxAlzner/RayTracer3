
echo "Installing dependencies"
mkdir -p deps
cd deps/

echo "rapidjson"

if [ ! -d rapidjson ]
then
    git clone https://github.com/miloyip/rapidjson.git
fi

cd rapidjson/
git pull origin
cmake ./
make
sudo make install
cd ../

echo "rapidxml"

if [ ! -d rapidxml ]
then
    git clone https://github.com/dwd/rapidxml.git
fi

cd rapidxml/
git pull origin
sudo cp -f ./*.hpp /usr/local/include/
cd ../

echo "glm"

if [ ! -d glm ]
then
    git clone https://github.com/g-truc/glm.git
fi

cd glm/
git pull origin
cmake ./
make
sudo make install
cd ../

echo "libshape"

if [ ! -d libshape ]
then
    git clone git@github.com:MaxAlzner/libshape.git
fi

cd libshape/
git pull origin
make
sudo make install
cd ../

cd ../