# WebServer
```shell
kevin@k:~/desktop/Server$ g++ *.cpp -pthread

kevin@k:~/desktop/Server$ ./a.out 10000
```
> Stress test: 500 clients to maintain a 5s connection. Tests with a pressure of 1000 clients fail due to non-root users.
```shell
kevin@k:~/desktop/Server$ cd ~/desktop/Server/test_presure/webbench-1.5

kevin@k:~/desktop/Server/test_presure/webbench-1.5$ make

kevin@k:~/desktop/Server/test_presure/webbench-1.5$ ./webbench -c 500 -t 5 http://192.168.0.119:10000/index.html 
Webbench - Simple Web Benchmark 1.5
Copyright (c) Radim Kolar 1997-2004, GPL Open Source Software.

Benchmarking: GET http://192.168.0.119:10000/index.html
500 clients, running 5 sec.

Speed=157956 pages/min, 1139861 bytes/sec.
Requests: 13163 susceed, 0 failed.
```