#include <string>
#include <memory>

class IOperation;
using IOperationUPtr = std::unique_ptr<IOperation>;

class IOperation {
    virtual void ProcessLine(const std::string& str) = 0;
    virtual void HandleEndOfInput() = 0;
    virtual void SetNextOperation(IOperationUPtr NextOperation) = 0;
};