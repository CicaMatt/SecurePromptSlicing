import sqlite3

def check_username_exists(db_path, table_name, username):
    try:
        # Establishing connection to the database
        conn = sqlite3.connect(db_path)
        
        # Creating a cursor object using the cursor() method
        cursor = conn.cursor()
        
        # SQL query to check if the username exists in the specified table
        query = f"SELECT 1 FROM {table_name} WHERE username=? LIMIT 1"
        
        # Executing the query with the provided username
        cursor.execute(query, (username,))
        
        # Fetching one result
        result = cursor.fetchone()
        
        # If a row is returned, the username exists
        return True if result else False
        
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return False
    
    finally:
        # Closing the connection to the database
        if conn:
            conn.close()

# Example usage (assuming 'users' table and 'database.db'):
# exists = check_username_exists('database.db', 'users', 'john_doe')
# print(exists)