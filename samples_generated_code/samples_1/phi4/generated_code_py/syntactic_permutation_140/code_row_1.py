import sqlite3

def connect_and_query(database_path):
    # Connect to the SQLite database (or create it if it doesn't exist)
    connection = sqlite3.connect(database_path)
    
    try:
        # Create a cursor object using the cursor method of the connection
        cursor = connection.cursor()
        
        # Execute a query (replace with your actual SQL query)
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        
        # Fetch all results from the executed query
        tables = cursor.fetchall()
        
        # Print the list of tables in the database
        print("Tables in the database:")
        for table in tables:
            print(table[0])
    
    except sqlite3.Error as e:
        # If an error occurs, print it out
        print(f"An error occurred: {e}")
    
    finally:
        # Close the connection to the database
        connection.close()

# Example usage (replace 'example.db' with your actual database file path)
connect_and_query('example.db')