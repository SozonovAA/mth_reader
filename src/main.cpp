#include <src/config/MyPrgConfig.h>

#include "include/search.h"
#ifdef USE_SOME_LIB

#endif

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include <chrono>


void myTask(const std::string & s, std::size_t time, std::uint16_t loop_c) {

    for(int i = 0; i < loop_c; i++){
        boost::this_thread::sleep_for(boost::chrono::milliseconds(time));
        std::cout << s << std::endl;
    }
    boost::this_thread::yield();
    return;
}

int main(){
    /*
     * Create an asio::io_service and a thread_group (through pool in essence)
     */
    boost::asio::io_service ioService;
    boost::thread_group threadpool;

    /*
     * This will start the ioService processing loop. All tasks
     * assigned with ioService.post() will start executing.
     */
    boost::asio::io_service::work work(ioService);

    /*
     * This will assign tasks to the thread pool.
     * More about boost::bind: "http://www.boost.org/doc/libs/1_54_0/libs/bind/bind.html#with_functions"
     */
    ioService.post(boost::bind(myTask, "1", 500, 5));
    ioService.post(boost::bind(myTask, "2", 1000, 5));
    ioService.post(boost::bind(myTask, "3", 100, 3));
    ioService.post(boost::bind(myTask, "4", 1000, 10));
//    ioService.poll();

    /*
     * This will add 2 threads to the thread pool. (You could just put it in a for loop)
     */
    threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService)
    );
    threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService)
    );
    threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService)
    );
    threadpool.create_thread(
        boost::bind(&boost::asio::io_service::run, &ioService)
    );

    ioService.post(boost::bind(myTask, "5", 1000, 4));



        /*
         * This will stop the ioService processing loop. Any tasks
         * you add behind this point will not execute.
        */
    ioService.stop();
    /*
     * Will wait till all the threads in the thread pool are finished with
     * their assigned tasks and 'join' them. Just assume the threads inside
     * the threadpool will be destroyed by this method.
     */
    threadpool.join_all();


}
