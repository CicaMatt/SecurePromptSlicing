import sqlite3

def connect_and_check_database(db_name, table_name):
    # Connect to SQLite database (or create it if it doesn't exist)
    connection = sqlite3.connect(db_name)
    
    try:
        cursor = connection.cursor()
        
        # Execute a query to check if the table exists
        cursor.execute(f"SELECT name FROM sqlite_master WHERE type='table' AND name='{table_name}';")
        
        result = cursor.fetchone()
        if result:
            print(f"The table '{table_name}' exists in the database.")
        else:
            print(f"The table '{table_name}' does not exist in the database.")
    
    finally:
        # Close the connection
        connection.close()

# Example usage
connect_and_check_database('example.db', 'my_table')