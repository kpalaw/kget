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

## The result screenshot
![Result return from google server.](https://github.com/kpalaw/kget/assets/16006116/b0be8b40-dd91-4a1a-8139-4fd6bce8afd9)


## kget Diagram

```mermaid
sequenceDiagram
kget ->> Server: HTTP Request: GET / HTTP/1.0\n\n
Note right of Server: If the requested pattern is ok it will return something back to kget.
Server-->>kget: <HTTP Header> + HTML 
```


