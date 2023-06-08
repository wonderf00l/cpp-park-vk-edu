#include "logger.hpp"

#include <memory>

SingletonLogger::SingletonLogger()
    : sink_{std::make_unique<CerrLoggerSink>()} {
}

SingletonLogger& SingletonLogger::get_instance() {
    static SingletonLogger singleton_;
    return singleton_;
}

void Log(LogLevel level, const std::string& msg) {
    SingletonLogger::get_instance().getSink().log(level, msg);
}

void SetGlobalLogger(std::unique_ptr<ILoggerSink> sink) { // клиент вызывает этот метод, выбирает один из импортированных логгеров, может реализовать свой, согласовывая реализацию с интерфейсом ILoggerSink
    SingletonLogger::get_instance().setSink(std::move(sink));
}
