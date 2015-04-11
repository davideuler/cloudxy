# 段文件管理 #
segment file 高效管理和使用是hlfs被用于在线系统的关键。因此我们将就下面几个功能进行开发。


## 段文件预先分配 ##
当前段文件创建是实时现场创建，熟悉hdfs的朋友都知道——创建过程需要和namenode交互。
显然当需要新的段文件时，再现场创建段一定会拖慢我们，所以我们要采取预分配方式:提前分配给定数量的段文件。从而避免每次现场创建的耗时。
实现方式：


## 段文件句柄池 ##
如果我们需要读取某个非当前段内数据，则要打开该段文件，读取完毕则关闭该段文件。打开和关闭都需要和namenode交互，显然这个消耗可不小。而读行为往往有一定的局部性，也就是说有可能反复打开某个段文件，所以我们可考虑使用句柄池的做法——类似于连接池吧。以减少读时重复打开段文件。
实现方式：

## 段文件预打开（甚至预读） ##
对于读操作来说，可以采用启发式预打开段文件，已加快读取速度。甚至可以进行预读操作。

## 段文件分目录 ##
当前我们所有段都”平坦“的位于uri指定的目录之下，没有层次之分。对于大量文件而言（上万），在其中检索段（比如在系统启动时，需要找到最后一个段），必然有所不便。因此可以考虑将段文件分目录存放，比如一个目录1000存放0-1000的段，2000存放1001-2000的段，如此以来检索某个段相对要简单不少了。