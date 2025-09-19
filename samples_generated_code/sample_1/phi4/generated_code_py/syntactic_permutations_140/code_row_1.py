import sqlite3

def connect_and_query(db_name, query):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect(db_name)

    try:
        # Create a cursor object using the cursor() method
        cursor = conn.cursor()

        # Execute SQL command
        cursor.execute(query)

        # Fetch all rows from the executed query
        results = cursor.fetchall()

        # Return the results
        return results

    except sqlite3.Error as e:
        print(f"Database error: {e}")

    finally:
        # Ensure the connection is closed even if an error occurs
        conn.close()

# Example usage
db_name = 'example.db'
query = "SELECT name FROM sqlite_master WHERE type='table';"
tables = connect_and_query(db_name, query)
print(tables)