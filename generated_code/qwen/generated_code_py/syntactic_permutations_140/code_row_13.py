import sqlite3

def check_username_exists(username):
    try:
        # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
        conn = sqlite3.connect('your_database.db')
        cursor = conn.cursor()
        
        # Execute a query to check if the username exists in the users table
        cursor.execute("SELECT 1 FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        
        # Return True if the username exists, otherwise return False
        return result is not None
    
    finally:
        # Ensure the connection is closed
        conn.close()

# Example usage
if __name__ == "__main__":
    username_to_check = "testuser"
    print(check_username_exists(username_to_check))