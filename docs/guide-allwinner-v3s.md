# 全志V3S，荔枝派(lichee-pi zero) <!-- {docsify-ignore} -->

## 编译源码，生成的目标文件在output目录下
```shell
make clean
make CROSS_COMPILE=/path/to/arm-none-linux-gnueabihf- PLATFORM=arm32-v3s
```

## 烧写到RAM中并运行
```shell
sudo xfel ddr v3s; sudo xfel write 0x40000000 xboot.bin; sudo xfel exec 0x40000000;
```

## 烧写普通镜像到SPI Flash
```shell
sudo xfel spinor write 0 xboot.bin
```

## 烧写压缩镜像到SPI Flash
```shell
sudo xfel spinor write 0 xboot.bin.z
```

## 下载xfel工具源码
```shell
git clone https://github.com/xboot/xfel.git
```

## 编译安装xfel工具
```shell
make
sudo make install
```

