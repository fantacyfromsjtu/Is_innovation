import sqlite3
import os

# 定义特征库文件的路径
pattern_file = os.path.join(os.path.dirname(__file__), 'patternfile.txt')

# 读取特征库文件内容
with open(pattern_file, 'r') as file:
    patterns = file.readlines()

# 创建或连接到SQLite数据库
conn = sqlite3.connect('pattern_database.db')
cursor = conn.cursor()

# 创建特征表
cursor.execute('''
CREATE TABLE IF NOT EXISTS patterns (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    pattern TEXT NOT NULL
)
''')

# 解析模式文件并插入到数据库中
for line in patterns:
    name, pattern = line.strip().split('#')
    cursor.execute('''
    INSERT INTO patterns (name, pattern)
    VALUES (?, ?)
    ''', (name, pattern))

# 提交更改并关闭数据库连接
conn.commit()
conn.close()

print("New pattern database created and populated successfully.")
