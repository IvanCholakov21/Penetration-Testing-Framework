#include "core/module.h"
#include <libssh/libssh.h>
#include <atomic>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <core/logger.h>

struct Credential{
    std::string username;
    std::string password;
};

class SSHAuthenticationAttempt {
    private:
    int timeout;
    int threads;
    Credential credential;
    ssh_session session;
    std::string host;
    int port;

    public:
    SSHAuthenticationAttempt(const std::string& h, int p = 22, int t = 5): host(h),port(p),timeout(t){
        session = ssh_new();

        if(session == NULL){
            Logger::error("Failed to create SSH session");
        }

    }

    ~SSHAuthenticationAttempt(){
        if(session){
            ssh_disconnect(session);
            ssh_free(session);
        }
    }

    bool connect(){
        ssh_options_set(session,SSH_OPTIONS_HOST,host.c_str());
        ssh_options_set(session,SSH_OPTIONS_PORT,&port);
        ssh_options_set(session,SSH_OPTIONS_TIMEOUT,&timeout);

        int re_code = ssh_connect(session);

        if(re_code != SSH_OK){
            Logger::error("Error connectings: Either connection refused, connection timeout or host unreachable");
            return false;
        }
        return true;
    }
    enum Authentication_Result {
        SUCCESS,
        FAILURE,
        ERROR,
        PARTIAL
    };

    Authentication_Result authenticate(const std::string& username, const std::string& password){
        int re_code = ssh_userauth_password(session, username.c_str(),password.c_str());
        switch(re_code){
            case SSH_AUTH_DENIED:
            return FAILURE;
            break;
            case SSH_AUTH_ERROR:
            Logger::error(std::string("Authenticaton error: ") + std::string(ssh_get_error(session)));
            return ERROR;
            break;
            case SSH_AUTH_PARTIAL:
            return PARTIAL;
            break;
            case SSH_AUTH_SUCCESS:
            return SUCCESS;
            break;
            default:
            Logger::error(std::string("Authenticaton error: ") + std::string(ssh_get_error(session)));
            return ERROR;
            
        }
    }
};

class ssh_bruteforce: public Module {

    private:
    std::queue<Credential> credential_queue;
    std::mutex queue_mutex;
    std::condition_variable condition_variable;
    std::vector<Credential> successful_credentials;
    std::mutex results_mutex;

    std::atomic<bool> stop_flag{false};
    std::atomic<int> attempts_made{0};
    std::atomic<int> successful_attempts{0};
    int max_threads;
    int delay_ms;


    public:


    std::string name() const override{
        return "SSH_Bruteforce";
    }


    std::string description() const override{
        return "Brute forcing in order to establish an ssh connection";
    }

    void run(const std::string target) override{

        std::vector<std::thread> threads;

        

    }

    void initialize_session(const std::string target) {

    }

    void load_credentials(){

    }

    void attempt_login(std::string username, std::string password){

    }
    
    void report_results(){

    }

    void worker_thread(){
        while(!stop_flag){
            Credential credential;
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                condition_variable.wait(lock, [this]{
                    return !credential_queue.empty() || stop_flag;
                });

                if(stop_flag && credential_queue.empty()){
                    return;
                }
                credential = credential_queue.front();
                credential_queue.pop();
            }
        }
    }


};