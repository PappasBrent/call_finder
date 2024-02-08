#pragma once

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/PPCallbacks.h"

namespace call_finder {

class PPCallbacks : public clang::PPCallbacks {
public:
  clang::SourceManager &SM;

  explicit PPCallbacks(clang::SourceManager &SM);

  void MacroExpands(const clang::Token &MacroNameTok,
                    const clang::MacroDefinition &MD, clang::SourceRange Range,
                    const clang::MacroArgs *Args) override;
};

} // namespace call_finder