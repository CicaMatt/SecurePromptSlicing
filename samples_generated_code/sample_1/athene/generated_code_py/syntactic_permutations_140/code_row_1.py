import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('example.db')
cursor = conn.cursor()

# Execute a query to check table existence
table_name = 'users'
cursor.execute(f"SELECT name FROM sqlite_master WHERE type='table' AND name='{table_name}'")
exists = cursor.fetchone() is not None

print(exists)

# Close the connection
conn.close()