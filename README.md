# xcc-posix

[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)

*A cross-platform C language wrapper library*



## Explain
By encapsulating the POSIX interface, a cross-platform call interface is provided.

At the same time, it provides convenient operation methods for some operations.

The project is the C language Api support library of the XCC series.



## Note
If you want to commit any changes, write the code in the following format.

set encoding=utf-8 with BOM

set tabstop=8

set shiftwidth=8




## Comment format

```shell
/// Function description
/// \param _Value : Parameter explanation
/// \return : Return value description
```



## Installation

### Linux

First install all required dependencies and build tools:
```shell
sudo apt install git
sudo apt install autoconf
sudo apt install automake
sudo apt install libtool-bin
sudo apt install cmake
```

Then clone the actual project repository:
```shell
git clone https://github.com/libxcc/xcc-posix.git
svn checkout https://github.com/libxcc/xcc-posix/trunk
cd xcc-posix
```

Now you can build and install it:
```shell
cmake .
make
sudo make install
```



## License

This library is licensed under the [GNU Lesser General Public License v2.1](https://www.gnu.org/licenses/lgpl-2.1.en.html),
also included in the repository in the `LICENSE` file.

README Updated on: 2023-04-10
