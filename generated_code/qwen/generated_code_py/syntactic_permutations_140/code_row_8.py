import sqlite3

def check_username_exists(username):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Execute a query to check if the username exists
    cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
    result = cursor.fetchone()
    
    # Close the connection
    conn.close()
    
    # Return True if the username exists, otherwise False
    return result is not None

# Example usage:
# print(check_username_exists('example_user'))