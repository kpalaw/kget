Simple HTTP Request

kget is a simple HTTP request programme. We can run kget <url> to get the web page 
eg. 
$kget www.google.com
which will return the html page (inclding its HTTP header) back but in the text form.

Install Boost. Run these commands in shell to install boost package.
$sudo apt update
$sudo apt install libboost-all-dev

How to Compile kget.
$g++ kget.cpp -o kget -lboost_regex

How to run kget. 
$kget <url> 

Example.
$kget
or 
$kget www.google.com
or





