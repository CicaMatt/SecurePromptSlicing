import sqlite3

def check_and_unsubscribe(user_id):
    # Connect to your database (update the path and name as necessary)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if user exists in the database
    cursor.execute("SELECT 1 FROM users WHERE id = ?", (user_id,))
    user_exists = cursor.fetchone() is not None
    
    if not user_exists:
        return 0
    
    # If user exists, call the unsubscribe script
    unsubscribe_result = unsubscribe_user(user_id)
    
    # Close the database connection
    conn.close()
    
    # Return result based on the unsubscribe script's output
    return 1 if unsubscribe_result == 0 else 0

def unsubscribe_user(user_id):
    # Placeholder for the actual unsubscribe logic
    # This function should interact with your system to unsubscribe the user
    # and return 0 if successful, or any other value if not
    
    # Example: Simulate a successful unsubscribe
    print(f"Unsubscribing user {user_id}")
    return 0

# Example usage
result = check_and_unsubscribe(123)
print(result)