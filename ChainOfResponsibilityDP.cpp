#include<bits/stdc++.h>
using namespace std;

class LogProcessor {
    public:
        static int INFO;
        static int DEBUG;
        static int ERROR;

        LogProcessor* nextLogProcessor;

        LogProcessor(LogProcessor* loggerProcessor) {
            this->nextLogProcessor = loggerProcessor;
        }

        virtual void log(int logLevel, string message) {
            if(nextLogProcessor != NULL) {
                nextLogProcessor->log(logLevel, message);
            }
        }  
};

int LogProcessor::INFO = 1;
int LogProcessor::DEBUG = 2;
int LogProcessor::ERROR = 3;


class InfoLogProcessor: public LogProcessor {
    public:
        InfoLogProcessor(LogProcessor* loggerProcessor) : LogProcessor(loggerProcessor) {}

        void log(int logLevel, string message) override {
            if(logLevel == INFO) {
                cout<<"INFO " + message<<endl;
            }
            else {
                LogProcessor::log(logLevel, message);
            }
        }
};

class DebugLogProcessor: public LogProcessor {
    public:
        DebugLogProcessor(LogProcessor* loggerProcessor) : LogProcessor(loggerProcessor) {}

        void log(int logLevel, string message) override {
            if(logLevel == DEBUG) {
                cout<<"DEBUG " + message<<endl;
            }
            else {
                LogProcessor::log(logLevel, message);
            }
        }
};

class ErrorLogProcessor: public LogProcessor {
    public:
        ErrorLogProcessor(LogProcessor* loggerProcessor) : LogProcessor(loggerProcessor) {}

        void log(int logLevel, string message) override {
            if(logLevel == ERROR) {
                cout<<"ERROR " + message<<endl;
            }
            else {
                LogProcessor::log(logLevel, message);
            }
        }
};


int main() {
    LogProcessor* logger = new InfoLogProcessor(new DebugLogProcessor(new ErrorLogProcessor(NULL)));

    logger->log(LogProcessor::INFO, "Info Log Print");
    logger->log(LogProcessor::DEBUG, "Debug Long Print");
    logger->log(LogProcessor::ERROR, "Error log print");

    delete logger;
}