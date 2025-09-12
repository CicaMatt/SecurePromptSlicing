import sqlite3

# Connect to the SQLite database (or any other database)
conn = sqlite3.connect('example.db')
cursor = conn.cursor()

# Execute a query to check something
query = "SELECT name FROM sqlite_master WHERE type='table';"
cursor.execute(query)

# Fetch and print the results
results = cursor.fetchall()
print(results)

# Close the connection
conn.close()