#include "call_finder/PPCallbacks.hh"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include <llvm-17/llvm/Support/raw_ostream.h>

namespace call_finder {

PPCallbacks::PPCallbacks(clang::SourceManager &SM) : SM(SM) {}

void PPCallbacks::MacroExpands(const clang::Token &MacroNameTok,
                               const clang::MacroDefinition &MD,
                               clang::SourceRange Range,
                               const clang::MacroArgs *Args) {
  auto Name = MacroNameTok.getIdentifierInfo()->getName();
  auto SourceLoc = Range.getBegin();
  auto SpellingLoc = SM.getSpellingLoc(SourceLoc);
  auto FunctionLike = MD.getMacroInfo()->isFunctionLike();

  llvm::outs() << "macro\t";
  llvm::outs() << Name << (FunctionLike ? "()" : "") << '\t';
  SpellingLoc.print(llvm::outs(), SM);
  llvm::outs() << '\n';
}
} // namespace call_finder
