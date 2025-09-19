import sqlite3

def does_username_exist(db_path, table_name, username):
    # Establish connection to the SQLite database
    conn = sqlite3.connect(db_path)
    
    try:
        # Create a cursor object using the connection
        cur = conn.cursor()
        
        # Prepare SQL query to check for existing username
        query = f"SELECT 1 FROM {table_name} WHERE username = ?"
        
        # Execute the query with the provided username
        cur.execute(query, (username,))
        
        # Fetch one record from the result set
        exists = cur.fetchone() is not None
        
        return exists
    
    finally:
        # Close the connection to the database
        conn.close()

# Usage example (uncomment and modify db_path and table_name as needed):
# print(does_username_exist('path_to_your_database.db', 'your_table_name', 'desired_username'))