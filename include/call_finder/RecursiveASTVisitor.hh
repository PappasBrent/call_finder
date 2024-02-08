#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceLocation.h"

namespace call_finder {

class RecursiveASTVisitor
    : public clang::RecursiveASTVisitor<RecursiveASTVisitor> {
public:
  clang::SourceManager &SM;

  RecursiveASTVisitor(clang::SourceManager &SM);

  bool VisitCallExpr(clang::CallExpr *CE);
};

} // namespace call_finder