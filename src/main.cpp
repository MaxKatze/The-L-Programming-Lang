#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

int main() {
    llvm::LLVMContext context;
    auto module = std::make_unique<llvm::Module>("L-Language", context);
    llvm::IRBuilder<> builder(context);

    auto *intType = llvm::Type::getInt64Ty(context);
    auto *funcType = llvm::FunctionType::get(intType, false);

    auto *func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "main",
        module.get()
    );

    auto *block = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(block);
    builder.CreateRet(llvm::ConstantInt::get(intType, 42));

    module->print(llvm::outs(), nullptr);
    return 0;
}