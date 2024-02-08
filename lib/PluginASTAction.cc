#include "call_finder/ASTConsumer.hh"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "llvm/ADT/StringRef.h"
#include <memory>

namespace call_finder {

class PluginASTAction : public clang::PluginASTAction {
public:
  PluginASTAction() : clang::PluginASTAction() {}

  PluginASTAction(PluginASTAction const &) = delete;

  PluginASTAction &operator=(PluginASTAction const &) = delete;

private:
  bool ParseArgs(clang::CompilerInstance const &,
                 std::vector<std::string> const &Args) override {
    return true;
  }

  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    llvm::StringRef InFile) override {
    return std::make_unique<ASTConsumer>(CI);
  }

  clang::PluginASTAction::ActionType getActionType() override {
    return clang::PluginASTAction::ActionType::AddBeforeMainAction;
  }
};

// Register the plugin with clang.
static clang::FrontendPluginRegistry::Add<PluginASTAction>
    X("call_finder", "Finds function and top-level macro calls");
} // namespace call_finder
