## PNG-supporting Libraries and Toolkits

- zlib is a general purpose data compression library, note that zlib is an integral part of libpng.

```
wget https://jaist.dl.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.gz

tar -xzvf zlib-1.2.11.tar.gz

cd zlib-1.2.11

./configure --prefix=$HOME/Project/ImageProcess/zlib

make && make install

```

- libpng, a reference library for supporting the Portable Network Graphics (PNG) format.

```
wget https://jaist.dl.sourceforge.net/project/libpng/libpng16/1.6.34/libpng-1.6.34.tar.gz

tar -xzvf libpng-1.6.34.tar.gz 

./configure --prefix=$HOME/Project/ImageProcess/libpng

make && make install
```
