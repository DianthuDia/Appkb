// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "../../common/hack/manifest.h"
#include "../../common/hack/targetver.h"

#define STRICT
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>
#include <ShellAPI.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください。


#include "../../common/hack/memory_leak.h"
#include "../../common/hack/reduce_page.h"

#include "../../common/config.h"
