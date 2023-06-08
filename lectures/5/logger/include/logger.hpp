#pragma once

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <memory>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

struct LoggerError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct ILoggerSink {
public:
    virtual ~ILoggerSink() {}
    virtual void log(LogLevel level, const std::string& msg) = 0;
};

class FileLoggerSink : public ILoggerSink {
public:
    FileLoggerSink(const std::string& name) {
        open(name);
    }

    void open(const std::string& name) {
        file_.open(name);
        if (!file_) {
            throw LoggerError{"Failed to open file"};
        }
    }

    void log(LogLevel level, const std::string& msg) override {
        file_ << msg << std::endl;
    }

private:
    std::ofstream file_;
};

class CerrLoggerSink : public ILoggerSink {
public:
    void log(LogLevel level, const std::string& msg) override {
        std::cerr << msg << std::endl;
    }
};

class SingletonLogger {
public:
    void setSink(std::unique_ptr<ILoggerSink> sink) {
        if (!sink) {
            throw LoggerError("Null ptr passed");
        }
        sink_ = std::move(sink);
    }

    ILoggerSink& getSink() {
        return *sink_;
    }

    static SingletonLogger& get_instance();

private:
    SingletonLogger();
    SingletonLogger(const SingletonLogger&) = delete;
    SingletonLogger& operator=(const SingletonLogger&) = delete;

    LogLevel min_level_;
    std::unique_ptr<ILoggerSink> sink_;
};

void Log(LogLevel level, const std::string& msg);
void SetGlobalLogger(std::unique_ptr<ILoggerSink> sink);

