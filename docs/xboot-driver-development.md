# 驱动开发 <!-- {docsify-ignore} -->
驱动开发是系统开发中的一个重要环节，也是XBOOT的两大核心关注点(驱动及应用)之一，在正式进入驱动开发之前，这里先介绍几个概念，了解了这些背景知识后，将有助于理解本章内容。驱动与设备是两个不同的概念，平时交流中，经常会混用两个概念，大家也不会觉得有违和感，那是因为大家将他们看成了一个整体，在理解具体要表达的内容上没有太大歧义。但是，在实际开发中，我们要严格区分这两个概念。驱动可类比为函数，是个执行机构，负责具体的执行动作；设备可类比为变量，用于描述自身属性。两者之间相互依存，缺一不可。系统中用哈希表分别管理了所有的驱动以及所有的设备，并为同种类型的设备提供了统一的操作接口。有了驱动及设备的概念后，为了进一步简化问题，这里引入了设备树的概念，设备树概念的引入，大大降低了添加设备的难度，很多时候，注册个新设备，仅仅需要填个设备属性描述就可以了。关于设备树的详细技术实现，参考后面章节的`设备树技术源码解析`。

## ADC驱动

ADC缩写`Analog to Digital Converter`，即模数转换器 ，能够将连续变化的模拟信号转换为离散的数字信号。真实世界中的模拟信号，例如温度、压力、声音或者图像等，都需要通过ADC变换后，才能够处理及存储。

### ADC驱动结构体定义

ADC驱动结构体，包含如下定义：

- 驱动名字
- 参考电压
- 采换精度
- 总通道数
- 采样接口
- 私有数据

```c
struct adc_t
{
	char * name;
	int vreference;
	int resolution;
	int nchannel;

	u32_t (*read)(struct adc_t * adc, int channel);
	void * priv;
};
```

### ADC设备搜索、注册及卸载

```c
struct adc_t * search_adc(const char * name);
struct device_t * register_adc(struct adc_t * adc, struct driver_t * drv);
void unregister_adc(struct adc_t * adc);
```

### ADC设备C API接口

```c
u32_t adc_read_raw(struct adc_t * adc, int channel);
int adc_read_voltage(struct adc_t * adc, int channel);
```

### ADC设备调试接口

当任何一个ADC设备在系统中成功注册后，在sysfs文件系统中，会自动导出以下调试接口，这些接口全是只读属性，可以通过`cat`指令来访问。

| 节点       | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| vreference | ADC参考电压                                                  |
| resolution | ADC采样精度                                                  |
| nchannel   | ADC通道数量                                                  |
| rawX       | 某个通道的采样原始值，`X`为通道数字编号，从0开始。           |
| voltageX   | 某个通道的采样原始值经转换后的电压值，`X`为通道数字编号，从0开始。 |

所有的adc设备驱动程序文件名，都是以`adc-`开头的`.c`文件，可以通过如下命令行搜索源码中所有的`ADC`驱动程序。

```shell
find . -name "adc-*.c"
```

## 音频驱动

## 电池电量驱动

## 块设备驱动

## 蜂鸣器驱动

## 时钟驱动

## 时钟事件驱动

## 时钟源驱动

## 超级终端驱动

## DAC驱动

## DMA驱动

## 显示屏驱动

## 重力传感器驱动

## GPIO驱动

## 湿度传感器驱动

## I2C总线驱动

## 输入设备驱动

## 中断控制器驱动

## 激光震镜驱动

## LED驱动

## 光线传感器驱动

## 马达驱动

## 非易失性存储器驱动

## PWM驱动

## 电压调节器驱动

## 复位驱动

## 随机数发生器驱动

## 实时时钟驱动

## SD卡驱动

## 伺服舵机驱动

## SPI总线驱动

## 步进电机驱动

## 温度传感器驱动

## 串口总线驱动

## 振动马达驱动

## 看门狗驱动

