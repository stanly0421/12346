# 12346

## Qt 簡易計算機 (Simple Qt Calculator)

這是一個使用 Qt5 開發的簡易計算機應用程式。

### 功能 (Features)
- 基本四則運算：加法 (+)、減法 (-)、乘法 (×)、除法 (÷)
- 小數點支援
- 清除 (C) 和全部清除 (AC) 功能
- 友好的圖形用戶界面

### 建置需求 (Build Requirements)
- Qt5 (Qt 5.15.13 或更高版本)
- qmake
- g++ 編譯器

### 安裝依賴 (Install Dependencies)
在 Ubuntu/Debian 系統上：
```bash
sudo apt-get update
sudo apt-get install -y qt5-qmake qtbase5-dev qtbase5-dev-tools
```

### 建置步驟 (Build Instructions)
```bash
qmake calculator.pro
make
```

### 執行 (Run)
```bash
./calculator
```

### 截圖 (Screenshot)
![Calculator Screenshot](https://github.com/user-attachments/assets/275d425e-eacc-4f30-a3f8-a7aade3c2e05)

### 專案結構 (Project Structure)
- `calculator.pro` - Qt 專案檔
- `main.cpp` - 應用程式進入點
- `calculator.h` - 計算機類別標頭檔
- `calculator.cpp` - 計算機實作檔