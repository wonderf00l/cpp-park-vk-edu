#include <IOperation.hpp>
#include <fstream>

using FileUPtr = std::unique_ptr<std::fstream, void(*)()>;

class CatOperation : public IOperation {
public:
    virtual void ProcessLine(const std::string& str) override;
    virtual void HandleEndOfInput() override;
    virtual void SetNextOperation(IOperationUPtr NextOperation) override;
private:
    FileUPtr pFile;
    std::string data;
};