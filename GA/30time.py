import subprocess
import re
import time
import pandas as pd

file_path = "result.xlsx"

# 初始化一個列表來保存結果
result_data = []

# 執行 GA.exe 30 次
for run in range(1, 31):
    # 執行 GA.exe 指令，計算執行時間
    start_time = time.time()
    subprocess.run(["GA.exe", "50"], text=True)
    end_time = time.time()

    # 等待一點時間確保文件已經寫入
    time.sleep(1)

    # 讀取文件
    with open(".\\GA_50_Queens.txt", "r") as file:
        output = file.read()

    # 使用正則表達式擷取 # of Queen attacks
    match = re.search(r'#\s*of\s*Queen\s*attacks:\s*(\d+)', output)

    if match:
        # 獲取攻擊數量
        attacks = int(match.group(1))

        # 計算執行時間
        execution_time = end_time - start_time

        # 將結果添加到列表
        result_data.append({"Run": run, "Attack Nums": attacks, "Execution Time (seconds)": execution_time})
    else:
        print(f"Failed to extract the number of Queen attacks in run {run}. Stopping.")
        break

# 將列表轉換為 DataFrame
result_df = pd.DataFrame(result_data)

# 將結果保存到 Excel 文件
result_df.to_excel(file_path, index=False)

print(f"Execution completed. Results saved in {file_path}.")
