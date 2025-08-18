import sqlite3

def check_query_result():
    conn = sqlite3.connect(':memory:')  # Connects to an in-memory SQLite database
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE test (id INTEGER)")
    cursor.execute("INSERT INTO test (id) VALUES (1)")
    conn.commit()
    
    # Query that should return no rows, hence False
    cursor.execute("SELECT * FROM test WHERE id = 2")
    result = cursor.fetchone()
    return result is None

# Execute the function and check it returns False
result = check_query_result()
print(result)