## Simple HTTP Client in C++
kget is a simple HTTP request programme. We can run kget <url> to get the web page eg. $kget [www.google.com](http://www.google.com), kget will return the html page back but in the text form.

## Install Boost Library
  
    $sudo apt update

    $sudo apt install libboost-all-dev



## **How to compile kget**

    $g++ kget.cpp -o kget -lboost_regex

## Run kget

    kget <url>
    
    For Example.
    $kget
    or
    $kget www.google.com


 ![The result will be like this](https://photos.app.goo.gl/49aaroD2LFDp7x6g8 "a title")
 
## kget Diagram

```mermaid
sequenceDiagram
kget ->> Server: HTTP Request: GET / HTTP/1.0\n\n
Note right of Server: If the requested pattern is ok it will return something back to kget.
Server-->>kget: <HTTP Header> + HTML 
```


