# A minimal qt example with cmake
use qt to display opencv image

Most of the code is borrowed from the Internet.
## How to use this code
```sh
sh build.sh
sh test.sh
```

## Intro to qt
1. **goal:** use Qt Designer to design the .ui file, and the use the .ui file in our cmake project.
1. The most useful guide is the offical link: [Using a Designer UI File in Your Application](http://www.bim-times.com/qt/Qt-5.11.1/qtdesigner/designer-using-a-ui-file.html).
In this code, we use the **Using a Pointer Member Variable** method of **The Single Inheritance Approach** in the above link.
1. Also, [AUTOUIC](https://cmake.org/cmake/help/latest/prop_tgt/AUTOUIC.html) is useful.

## Some hints to the code

1. In the `CMakeLists.txt` file, we set the `CMAKE_AUTOMOC` option, so according to  [AUTOUIC](https://cmake.org/cmake/help/latest/prop_tgt/AUTOUIC.html), when we use `#include "ui_cameras.h"` in `mycamera.h`, `AUTOUIC` will try to find `cameras.ui` in the folder and generate `ui_cameras.h` in the build directory.
2. we have a `openCamera` button in `cameras.ui`. If we want to write a slot to process the clicke event, we only need to write `void on_<object name>_<signal name>(<signal parameters>);`, it wil use QMetaObject's auto-connection facilities to connect the OK button's clicked() signal to a slot in our subclass. (this is also in [Using a Designer UI File in Your Application](http://www.bim-times.com/qt/Qt-5.11.1/qtdesigner/designer-using-a-ui-file.html))
