import sqlite3

# Connect to the SQLite database (or create it if it doesn't exist)
connection = sqlite3.connect('example.db')
cursor = connection.cursor()

# Create a table if it doesn't already exist
cursor.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)''')

# Execute a query to check if the table has any data
cursor.execute('SELECT * FROM users')

# Fetch all results from the executed query
results = cursor.fetchall()

# Print the results
print(results)

# Close the connection
connection.close()