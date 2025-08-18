import sqlite3

def check_query():
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Create a table for demonstration purposes
    cursor.execute('''CREATE TABLE IF NOT EXISTS test_table (id INTEGER PRIMARY KEY, value TEXT)''')
    
    # Insert some data for testing
    cursor.execute("INSERT INTO test_table (value) VALUES ('test')")
    conn.commit()
    
    # Execute a query that should return False
    cursor.execute("SELECT * FROM test_table WHERE id = 0")
    result = cursor.fetchone()
    
    # Check if the result is None (False in this context)
    if not result:
        print(False)
    else:
        print(True)
    
    # Close the connection
    conn.close()

check_query()