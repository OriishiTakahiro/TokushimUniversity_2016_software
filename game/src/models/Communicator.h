
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#include <mutex>
#include <thread>

std::mutex mtx;

class Communicator{

 private :
	LinkedList <CustomizedRumba*>;
	RunawayRumba* runaway_runmba;
	pthread_mutex_t receiver_mutex ;
	pthread_mutex_t sender_mutex  ;
	
		
 public : 
	void sendData(vector<char> &data){
	
	}
	
	void receiveData(vector<char> &data){
	//objects.json
	
         }
         
         
	void startCommunication(void){
	//何に使う＞？
	} 
	
	void handShake(){}
	
	void Mutex(){
	mtx.lock();
	//処理を行ったらロックの状態を戻す。
	mtx.unlock();
	}　
	　
	void lockMutex(){
	mtx.lock();
	}
	void unlockedMutex(){
	mtxunlock();
	}
    

    
