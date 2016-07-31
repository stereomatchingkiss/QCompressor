# Synopsis

A simple command line tools to zip/unzip files/folders by the qCompress api provided by Qt5.

# Dependencies

The dependencies of this project are

1. [Qt5.6.x](https://www.qt.io/download-open-source/#section-2)
2. [qt_enhance/compressor](https://github.com/stereomatchingkiss/qt_enhance/tree/master/compressor)

#How to build them

##Qt5.6.x

Community already build it for us, just download the installer suit your os and compiler.

##qt_enhance/compressor

Include the sources files 

1. file_compressor.cpp
2. folder_compressor.cpp

into your make file

#How to use it

This program use text file to indicate the files/folders you want to compress/decompress, 
by default the text file of compress is "compress_data.txt", the text file of decompress is
"decompress_data.txt".

##Command line examples

Load targets from default text file
```
QCompressor
```

Load targets from new text file
```
QCompressor my_compress.txt my_decompress.txt
```

##Compress

Specify the file/folder you want to compress, and the desire output.Example

```
C:/Users/yyyy/Qt/jobs/build-turf_club_statistic-Qt5_6_0_vc2015_32-Release/turf_club_statistic/turfclub_SingaporeRaceCard.sqlite turfclub_SingaporeRaceCard.sqlite.zip 
C:/Users/yyyy/Qt/jobs/build-turf_club_statistic-Qt5_6_0_vc2015_32-Release/turf_club_statistic/color color.zip
```

First column is the file/folder you want to compress, second column is the absolute path after compress

##Decompress

Specify the file/folder you want to decompress, and the desire output.Example

```
file turfclub_SingaporeRaceCard.sqlite.zip turfclub_SingaporeRaceCard.sqlite
folder color.zip color
```

First column is the type (file or folder) you want to decompress, second column is the absolute path of the file 
you want to decompress, third column is the absolute path after decompress

# Bugs report and features request

If you found any bugs or any features request, please open the issue at github.
I will try to solve them when I have time.
