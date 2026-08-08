// This alone cost me my sanity to build. It took along time but it was cuz of me being lazy
#pragma once

#include "converter.hpp"
#include <QKeySequence>
#include <cstdlib>

UINT convert_QKey_UINT(
    const void *QKey) { // void* is not nice. it may break the code.

  if (!QKey) {
	  std::abort();
  }
  const QKeySequence *qtKey = static_cast<const QKeySequence *>(QKey);

  Qt::Key key = (*qtKey)[0].key();

switch(key){
#define X(name, qt, vk) case qt: return vk;
#include "keylist.def" //This file was AI generated since it was repetative hell. Be extra careful with it.
#undef X
default:
  return 0;
}
}
