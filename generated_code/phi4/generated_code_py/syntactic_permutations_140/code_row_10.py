import sqlite3

# Establish connection to an in-memory SQLite database (or change 'example.db' to your actual database file)
conn = sqlite3.connect(':memory:')  # Use ':memory:' for an in-memory database or specify the filename like 'example.db'
cursor = conn.cursor()

# Create a sample table
cursor.execute('CREATE TABLE test_table (id INTEGER PRIMARY KEY, name TEXT)')

# Insert some data into the table
cursor.execute('INSERT INTO test_table (name) VALUES ("Sample Name")')
conn.commit()

# Execute a query to check if it returns False by checking for an empty result set
query = 'SELECT * FROM test_table WHERE id = 999'  # This ID does not exist in our sample data

try:
    cursor.execute(query)
    result = cursor.fetchone()
    query_returns_false = (result is None)  # True if the result is None, meaning no rows were returned
finally:
    conn.close()

print(f"Query returns false: {query_returns_false}")