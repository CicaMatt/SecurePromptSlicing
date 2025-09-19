import sqlite3

def check_database():
    try:
        # Connect to SQLite database (or create it if it doesn't exist)
        conn = sqlite3.connect('example.db')
        cursor = conn.cursor()
        
        # Create a table for demonstration purposes
        cursor.execute('''CREATE TABLE IF NOT EXISTS users
                          (id INTEGER PRIMARY KEY, name TEXT)''')
        
        # Insert a sample record
        cursor.execute("INSERT INTO users (name) VALUES ('Alice')")
        
        # Execute a query to check if the record exists
        cursor.execute("SELECT * FROM users WHERE name='Alice'")
        result = cursor.fetchone()
        
        if result:
            print("Record found:", result)
        else:
            print("No record found.")
    
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        # Close the connection
        if conn:
            conn.close()

check_database()