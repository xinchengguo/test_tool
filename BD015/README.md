# 用于BD015保护板的半成品保护板相关说明

## BD015是双5串级联的10串保护板，检查过压保护时需对前5串和后5串分别进行检查

## 根据硬件设计的需求,软件只需要采样三个点位的电压的信息,来判断保护板是否符合设计要求,具体点位参考原理图

### 测试点1 NTC检查

        NTC分压值应在2800mV和3730mV

### 测试点2 5串电压检查

        根据硬件设计，只需要测量前5串电池总电压，分压值在1700mV在1900mV范围内

### 测试点3 过压保护反馈

- 首先对前5串进行过压反馈检查，如果反馈电平正常，进行下一步检查
- 如果前5串反馈正常，则进行后5串电芯过压检查，这一步反馈正常，即认为该PCBA功能正常
