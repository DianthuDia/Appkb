#include "../../common/typedef.h"
#include "Resource.h"

#include "CHook.h"

LRESULT CALLBACK MainProc(IN HWND hWnd, IN UINT msg, IN WPARAM wp, IN LPARAM lp);
VOID AddTaskbar(IN HWND hWnd, OUT PNOTIFYICONDATA lpNid);
VOID DelTaskbar(IN PNOTIFYICONDATA lpNid);
VOID ShowTaskbarMenu(IN HWND hWnd);
