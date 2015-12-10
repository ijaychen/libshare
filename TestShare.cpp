#include "Test.h"
#include "Callback.h"
#include "Timer.h"
#include "TimerQueue.h"
#include "HttpMgr.h"
#include <string>
using namespace std;
int main()
{
	Test::create_instance();
	sTest.run();
	Callback * cb = Callback::bind(Test::instance(), &Test::CallbackFunc);
	cb->run();
	cout << "========1==========\n";
	cout << "now64:" << now64() << endl;
	cout << "now:" << now() << endl;
	cout << "tick:" << tick() << endl;
	
	cout << "========2==========\n";
	/// timer q
    TimerQueue<> _tq;
	_tq.add_timer(1000, Callback::bind(Test::instance(), &Test::send_ping_msg),1);
	int cnt = 0;
	while(cnt < 10)
	{
		uint64 t = now64();
        while (_tq.expire(t) == 0)
		{
			cout << "now64:" << t << endl;
			cnt++;
		}
	}
	cout << "======3============\n";
	HttpMgr::create_instance();
	if (!sHttpMgr.open(1))
	{
		cout << "===== failed to start http mgr! =====\n";
		return 1;
	}
	// execute
    string webret;
	if (!sHttpMgr.get("http://192.168.0.23/orange/user/reg_acct.php",
                          HttpMgr::QStr()
                                .add("deviceId", "122221eee")
                                .add("acct", "jason")
                                .add("pwd", "123456"),
                          webret))
						  {
							  cout << "sHttpMgr.get error" << endl;
						  }

        // parse result
        // check error code
        int ret = atoi(webret.c_str());
		cout << "ret:" << ret << endl;

	
	sHttpMgr.close();
	return 0;
}