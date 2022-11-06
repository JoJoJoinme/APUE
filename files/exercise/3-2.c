// to be done, 不清楚如何在一个指定的fd上打开文件.
// refer: https://blog.csdn.net/chenyufei1013/article/details/6802632
// 思路是利用dup永远返回最小可以fd,那么一直调用dup，直至返回期望的fd，再退出。算取巧吧
