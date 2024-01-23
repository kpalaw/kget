
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h> 
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <cassert>
#include <boost/regex.hpp>




using namespace std;

class myUrl {
	private:
       
    int r,w,wtotal=0;
    char c;
    int count=0;

		int sockfd;
		struct sockaddr_in serveraddr;
		char buf[1000000];
		struct hostent *hostptr;
    struct in_addr *ptr;

    bool showHeader = true;

    string reqMsg ="GET / HTTP/1.0\n\n"; //GET + ServicePoint + HTTP/1.0\n\n
    string domainName="www.google.com";
    string servicePoint="/";
    string ServerAddr; //ip address of Server, default to www.google.com 
    int ServerPort=80;

    
    void setReqMsg(string cmd){
      reqMsg.clear();
      reqMsg+=cmd;
    }
    void setDomainName(string dn){
      domainName.clear();
      domainName+=dn;
    }

    int setServerAddr(string domainName){
    //if success return 0
    //if error return negative number

      ServerAddr.clear();
      hostptr=gethostbyname(domainName.c_str()); //if there is / at the end we must delete it. Only host name is allowed
      if (hostptr == nullptr) {
        cerr << "Name Error:can not find IP Address for:" << domainName.c_str() << endl;
        return -1;
      }
      ptr=(struct in_addr *) *(hostptr->h_addr_list);
      ServerAddr = inet_ntoa(*(ptr));
      
      return 0;
    }

    void setServicePoint(string sp){
      servicePoint.clear();
      servicePoint+= sp;
      
    }

	public:
	myUrl(){
    setServerAddr("www.google.com");
    setServicePoint("/");
	
  }
  void setShowHeader(bool t){
    showHeader = t;
  }
  bool getShowHeader(){
    return showHeader;
  }

  void getWeb(const string url){
    
    boost::regex regExFull("^http://(www.[a-z]+.[a-z.]{2,})(/[a-z/.]+)"); //Full: http+www+Service(eg. index.html)
    boost::regex regExHttpWww("^http://(www.[a-z]+.[a-z.]{2,})"); //http+www
    boost::regex regExWwwIndex("(www.[a-zA-Z0-9]+.[a-zA-Z.]{2,})(/[a-zA-Z0-9./]+)"); //www + index
    boost::regex regExWww("(^www.[a-z]+.[a-z.]{2,})"); //www 
    
    boost::smatch matchStr;

    if (regex_search(url, matchStr, regExFull)){//http+www+index
            
      setServicePoint(matchStr[2].str());
      int ipDone = setServerAddr(matchStr[1].str().c_str());
      if (ipDone >= 0) {
        setReqMsg("GET " + servicePoint+ " HTTP/1.0\n\n");
        getWeb();
        return;
      }else {
        exit(0);
      }   
    }

    if (regex_search(url, matchStr, regExHttpWww)){//http + www
            
      setServicePoint("/");
      int ipDone = setServerAddr(matchStr[1].str().c_str());
      if (ipDone >= 0) {
        setReqMsg("GET " + servicePoint+ " HTTP/1.0\n\n");
        getWeb();
        return;
      }else {
        exit(0);
      }   
    }
  
  if (regex_search(url, matchStr, regExWwwIndex)){//www + service
            
      setServicePoint(matchStr[2].str());
      int ipDone = setServerAddr(matchStr[1].str().c_str());
      if (ipDone >= 0) {
        setReqMsg("GET " + servicePoint+ " HTTP/1.0\n\n");
        getWeb();
        return;
      }else {
        exit(0);
      }   
    }


if (regex_search(url, matchStr, regExWww)){//www
            
      setServicePoint("/");
      int ipDone = setServerAddr(matchStr[1].str().c_str());
      if (ipDone >= 0) {
        setReqMsg("GET " + servicePoint+ " HTTP/1.0\n\n");
        getWeb();
        return;
      }else {
        exit(0);
      }   
    }

  }//end 



	void getWeb(){
  
    memset((char*)&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr(ServerAddr.c_str());
    serveraddr.sin_port=htons(ServerPort);

    if ( (sockfd=socket(AF_INET,SOCK_STREAM,0))<0){
      cerr << "Can not create Socket" << endl;
      exit(1);
    }

    if (connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
      cerr << "Can not connet to server" << endl;
      exit(1);
    }

    //send request to server with reqMsg
    w=write(sockfd, reqMsg.c_str(), reqMsg.length()); //write command to server

    do{
      r=read(sockfd,&c,1);
      buf[count]=c;
      count++;
    }while(!(buf[count-1]=='\n'&&buf[count-2]=='\r'&&buf[count-3]=='\n'&&buf[count-4]=='\r'));
    buf[count]='\0';
    if (getShowHeader() == true) {
    //show Header 
      cout << buf ;  
    }


    memset((char*)&buf, 0, sizeof(buf));

    count=0;
    while( (r=read(sockfd,buf,sizeof(buf)-1)) >0) {
      cout << buf ;
      memset((char*)&buf, 0, sizeof(buf));
    }

    cout << endl;
    close(sockfd);
  }

};

int main(int argc,char* argv[]){

	myUrl ReqAndRes;

    if (argc >=2 ) {
      ReqAndRes.getWeb(argv[1]);
    } else{
      ReqAndRes.getWeb(); //default to www.google.com 
    }
    

    ReqAndRes.getWeb();   
    ReqAndRes.getWeb();  
    return 0;
}

