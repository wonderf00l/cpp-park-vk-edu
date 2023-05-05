#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

class IOperation {
public:
    virtual void ProcessLine(const std::string& str) = 0;
    virtual void HandleEndOfInput() = 0;
    virtual void SetNextOperation(std::unique_ptr<IOperation> next_operation) = 0;
};

class CatOperation : public IOperation {
public:
    explicit CatOperation(const std::string& filename) : filename_(filename) {}

    void ProcessLine(const std::string& str) override {
        lines_.push_back(str);
    }

    void HandleEndOfInput() override {
        std::ifstream file(filename_);
        std::string line;
        while (std::getline(file, line)) {
            lines_.push_back(line);
        }
        if (next_operation_) {
            for (const auto& line : lines_) {
                next_operation_->ProcessLine(line);
            }
            next_operation_->HandleEndOfInput();
        } else {
            for (const auto& line : lines_) {
                std::cout << line << std::endl;
            }
        }
    }

    void SetNextOperation(std::unique_ptr<IOperation> next_operation) override {
        next_operation_ = std::move(next_operation);
    }

private:
    std::vector<std::string> lines_;
    std::unique_ptr<IOperation> next_operation_;
    const std::string filename_;
};

class EchoOperation : public IOperation {
public:
    explicit EchoOperation(const std::string& str) : str_(str) {}

    void ProcessLine(const std::string& str) override {}

    void HandleEndOfInput() override {
        if (next_operation_) {
            next_operation_->ProcessLine(str_);
            next_operation_->HandleEndOfInput();
        } else {
            std::cout << str_ << std::endl;
        }
    }

    void SetNextOperation(std::unique_ptr<IOperation> next_operation) override {
        next_operation_ = std::move(next_operation);
    }

private:
    const std::string str_;
    std::unique_ptr<IOperation> next_operation_;
};

class TailOperation : public IOperation {
public:
    explicit TailOperation(int n) : n_(n) {}

    void ProcessLine(const std::string& str) override {
        if (lines_.size() == n_) {
            lines_.erase(lines_.begin());
        }
        lines_.push_back(str);
    }

    void HandleEndOfInput() override {
        if (next_operation_) {
            for (const auto& line : lines_) {
                next_operation_->ProcessLine(line);
            }
            next_operation_->HandleEndOfInput();
        } else {
            for (const auto& line : lines_) {
                std::cout << line << std::endl;
            }
        }
    }

    void SetNextOperation(std::unique_ptr<IOperation> next_operation) override {
        next_operation_ = std::move(next_operation);
    }

private:
    int n_;
    std::vector<std::string> lines_;
    std::unique_ptr<IOperation> next_operation_;
};

int main(int argc, char* argv[]) {

  std::vector<std::unique_ptr<IOperation>> operations;
  int i = 1;
  while (i < argc) {

    const auto arg = argv[i];
    if (arg == "|") {
        operations.back()->SetNextOperation(std::move(operations[operations.size() - 2]));
        operations.pop_back();
    } else if (arg == "cat") {
        operations.push_back(std::make_unique<CatOperation>(argv[i]));
    }
  }
}