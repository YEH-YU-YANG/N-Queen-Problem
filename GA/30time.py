import subprocess
import re
import time
import pandas as pd
import sys

# 確保檔頭使用 UTF-8 編碼，以支援中文字符
# -*- coding: utf-8 -*-

# 確保命令行參數的數量正確
if len(sys.argv) != 2:
    print("請提供一個數字作為參數，例如：python your_script.py 8")
    sys.exit(1)

# 從命令行參數中獲取數字
number_of_queens = sys.argv[1]

file_path = "result.xlsx"
result_data = []

for run in range(1, 31):
    start_time = time.time()
    
    # 將使用者輸入的數字傳遞給 GA.exe
    subprocess.run(["GA.exe", number_of_queens], text=True)
    
    end_time = time.time()

    time.sleep(1)

    with open(f".\\GA_{number_of_queens}_Queens.txt", "r") as file:
        output = file.read()

    match = re.search(r'#\s*of\s*Queen\s*attacks:\s*(\d+)', output)

    if match:
        attacks = int(match.group(1))
        execution_time = end_time - start_time
        result_data.append({"Run": run, "Attack Nums": attacks, "Execution Time (seconds)": execution_time})
    else:
        print(f"無法在第 {run} 次運行中提取皇后攻擊數。停止執行。")
        break

result_df = pd.DataFrame(result_data)
result_df.to_excel(file_path, index=False)

print(f"執行完成。結果保存在 {file_path}。")
