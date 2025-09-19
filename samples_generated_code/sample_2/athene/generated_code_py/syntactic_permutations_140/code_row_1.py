import sqlite3

# Connect to the SQLite database
conn = sqlite3.connect('example.db')
cursor = conn.cursor()

# Execute a query to check something (e.g., count of rows in a table)
cursor.execute("SELECT COUNT(*) FROM some_table")
result = cursor.fetchone()

print(result)

# Close the connection
conn.close()