#include "call_finder/RecursiveASTVisitor.hh"
#include "clang/AST/Decl.h"
#include "clang/AST/Expr.h"
#include "clang/Basic/SourceManager.h"
#include <llvm-17/llvm/Support/Casting.h>
#include <llvm-17/llvm/Support/raw_ostream.h>

namespace call_finder {

RecursiveASTVisitor::RecursiveASTVisitor(clang::SourceManager &SM) : SM(SM) {}

bool RecursiveASTVisitor::VisitCallExpr(clang::CallExpr *CE) {
  auto D = CE->getCalleeDecl();
  if (!D) {
    return true;
  }

  auto FD = llvm::dyn_cast_or_null<clang::FunctionDecl>(D);
  if (!FD) {
    return true;
  }

  auto Name = FD->getName();
  auto SourceLoc = CE->getBeginLoc();
  auto SpellingLoc = SM.getSpellingLoc(SourceLoc);

  llvm::outs() << "function\t" << Name << "\t";
  SpellingLoc.print(llvm::outs(), SM);
  llvm::outs() << '\n';

  return true;
}

} // namespace call_finder