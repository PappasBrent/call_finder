#include "call_finder/ASTConsumer.hh"
#include "call_finder/PPCallbacks.hh"
#include "call_finder/RecursiveASTVisitor.hh"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include <memory>

namespace call_finder {
ASTConsumer::ASTConsumer(clang::CompilerInstance &CI) {
  auto &PP = CI.getPreprocessor();
  PP.addPPCallbacks(std::make_unique<PPCallbacks>(CI.getSourceManager()));
}

void ASTConsumer::HandleTranslationUnit(clang::ASTContext &Ctx) {
  auto &SM = Ctx.getSourceManager();
  auto TUD = Ctx.getTranslationUnitDecl();
  auto Visitor = RecursiveASTVisitor(SM);
  Visitor.TraverseDecl(TUD);
}
} // namespace call_finder