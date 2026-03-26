<p align="center">
  <img width="128" height="128" alt='Assistant.nvim Logo' src="https://github.com/user-attachments/assets/720b55eb-9fa3-4eb7-9bc0-a439859d007f" />
</p>

<h1 align="center">Assistant.nvim</h1>

<p align="center">
  <img alt="Latest release" src="https://img.shields.io/github/v/release/A7Lavinraj/assistant.nvim?style=for-the-badge&logo=starship&color=C9CBFF&logoColor=D9E0EE&labelColor=302D41&include_prerelease&sort=semver" />
  <img alt="License" src="https://img.shields.io/github/license/A7Lavinraj/assistant.nvim?style=for-the-badge&logo=starship&color=ee999f&logoColor=D9E0EE&labelColor=302D41" />
  <img alt="Stars" src="https://img.shields.io/github/stars/A7Lavinraj/assistant.nvim?style=for-the-badge&logo=starship&color=c69ff5&logoColor=D9E0EE&labelColor=302D41" />
</p>

<p align="center">A powerful and efficient Neovim plugin designed for competitive programmers. It automates the testing workflow, making it faster and more convenient to run test cases directly inside Neovim</p>

<br>

<div align="center">

  ![showcase](https://github.com/user-attachments/assets/3f4e910e-deea-4946-ad0d-7ab2541084f7)

</div>

<br>

> [!NOTE]
> Speed is crucial in competitive programming. Ensure that using this plugin enhances your workflow rather than slowing you down.

<br>

## Features

- **Automated Test Case Management**: Easily fetch and organize test cases from online judges.
- **Customizable Execution Commands**: Support for multiple programming languages with configurable commands.
- **Interactive UI**: A user-friendly interface for managing test cases.
- **Asynchronous Processing**: Ensures Neovim remains responsive during execution.

<br>

## Requirements

- **Neovim** `>= 0.9.5`
- [Competitive Companion Browser Extension](https://github.com/jmerle/competitive-companion)

<br>

## Installation Using [lazy.nvim](https://github.com/folke/lazy.nvim)

### latest version

```lua
{
    'A7lavinraj/assistant.nvim',
    lazy = false,
    keys = {
        { '<leader>a', '<cmd>Assistant<cr>', desc = 'Assistant.nvim' }
    },
    opts = {}
}
```

### stable version

```lua
{
    'A7lavinraj/assistant.nvim',
    branch = 'stable',
    lazy = false,
    keys = {
        { '<leader>a', '<cmd>Assistant<cr>', desc = 'Assistant.nvim' }
    },
    opts = {}
}
```

<br>

## Default configuration

```lua
{
    mappings = {},
    commands = {
        python = {
            extension = 'py',
            template = nil,
            compile = nil,
            execute = {
                main = 'python3',
                args = { '$FILENAME_WITH_EXTENSION' },
            },
        },
        cpp = {
            extension = 'cpp',
            template = nil,
            compile = {
                main = 'g++',
                args = { '$FILENAME_WITH_EXTENSION', '-o', '$FILENAME_WITHOUT_EXTENSION' },
            },
            execute = {
                main = './$FILENAME_WITHOUT_EXTENSION',
                args = nil,
            },
        },
    },
    ui = {
        border = 'single',
        diff_mode = false,
        title_components_separator = '',
    },
    core = {
        process_budget = 5000,
        port = 10043,
        filename_generator = nil
    },
}
```

<br>

## LeetCode 整合

Assistant.nvim 搭配自訂的 [Competitive Companion](https://github.com/jmerle/competitive-companion) LeetCode parser，提供完整的本地測試流程。

### 運作原理

1. Competitive Companion 的 LeetCode parser 從題目頁面擷取測試資料和函式簽名
2. 當收到的資料包含 `srcCode` 欄位時，assistant.nvim 會用它來填入原始碼，取代靜態 template
3. Parser 會自動產生 `main()` 函式，從 stdin 讀取參數並呼叫 Solution 方法，不需手動寫樣板程式碼

### 設定

1. **安裝自訂的 Competitive Companion**（含 LeetCode 支援）並建置擴充套件
2. **設定 assistant.nvim** 使用 GNU g++（macOS 的 clang 不支援 `bits/stdc++.h`）：

> **Note:** `leetcode_io.h`（提供 `lc_read()` / `lc_print()`）已內建於 plugin 中，編譯時會自動加入 include 路徑，不需手動建立。

```lua
{
    'A7lavinraj/assistant.nvim',
    lazy = false,
    keys = {
        { '<leader>a', '<cmd>Assistant<cr>', desc = 'Assistant.nvim' },
    },
    opts = {
        commands = {
            cpp = {
                extension = 'cpp',
                compile = {
                    main = 'g++-13',  -- 使用 GNU g++，不要用 Apple clang
                    args = { '-std=c++17', '-O2', '$FILENAME_WITH_EXTENSION', '-o', '$FILENAME_WITHOUT_EXTENSION' },
                },
                execute = {
                    main = './$FILENAME_WITHOUT_EXTENSION',
                    args = nil,
                },
                template = vim.fn.stdpath('config') .. '/templates/leetcode.cpp',
            },
        },
    },
}
```

### 使用流程

1. 在你的 leetcode 工作目錄開啟 Neovim
2. 執行 `:AssistantTCPStart` 開始監聽
3. 在瀏覽器開啟 LeetCode 題目，點擊 Competitive Companion 按鈕
4. 在選擇器中選 `cpp` — 自動建立 `.cpp` 檔案，內含 Solution class 和自動產生的 `main()`
5. 在 Solution class 中寫你的解法
6. `<leader>a` 開啟 Assistant 面板，按 `r` 執行測試
7. 在面板中按 `y` 複製 Solution class 到剪貼簿，直接貼到 LeetCode 提交

### 面板快捷鍵

| 鍵 | 功能 |
|-----|--------|
| `r` | 執行測試案例 |
| `y` | 複製 Solution class 到剪貼簿 |
| `s` | 選取/取消選取當前測試案例 |
| `a` | 全選/全取消 |
| `c` | 新增測試案例 |
| `d` | 刪除測試案例 |
| `e` | 編輯測試案例 |
| `i` | 互動模式執行 |
| `?` | 顯示所有快捷鍵 |
| `q` | 關閉面板 |

### 產生的程式碼結構

```cpp
#include <bits/stdc++.h>
using namespace std;
#include "leetcode_io.h"

class Solution {                // <-- 提交時複製這段
public:
    int example(vector<int>& nums) {
        // 你的解法
    }
};                              // <-- 複製到這裡

int main() {                    // 自動產生，僅用於本地測試
    Solution sol;
    vector<int> nums;
    lc_read(nums);
    lc_print(sol.example(nums));
    return 0;
}
```

<br>

<h4 align="center">
  <span>Explore more about assistant on</span>
  <a href="https://github.com/A7Lavinraj/assistant.nvim/wiki">Wiki</a>
</h4>

<div align="center">
  <h2>Want to contribute?</h2>

  Please read [CONTRIBUTING.md](https://github.com/A7Lavinraj/assistant.nvim/blob/main/CONTRIBUTING.md) to get started
</div>
