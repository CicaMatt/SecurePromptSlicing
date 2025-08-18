import sqlite3

def check_if_exists(db_name, table_name, column_name, value):
    conn = None
    try:
        # Connect to the SQLite database (or create it if it doesn't exist)
        conn = sqlite3.connect(db_name)
        
        # Create a cursor object using the connection
        cur = conn.cursor()
        
        # Construct and execute the SQL query
        query = f"""
        SELECT EXISTS(
            SELECT 1 FROM {table_name}
            WHERE {column_name} = ?
        )
        """
        
        cur.execute(query, (value,))
        
        # Fetch the result from the cursor
        exists = cur.fetchone()[0]
        
        return bool(exists)
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if conn:
            # Close the connection to the database
            conn.close()

# Example usage:
result = check_if_exists('example.db', 'users', 'username', 'john_doe')
print(result)