import sqlite3

def check_and_unsubscribe(user_id):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Check if user exists in the database
    cursor.execute("SELECT * FROM users WHERE id=?", (user_id,))
    user_exists = cursor.fetchone() is not None
    
    conn.close()
    
    if not user_exists:
        return 0
    
    # Call the unsubscribe script
    result = unsubscribe_script(user_id)
    
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_script(user_id):
    # This function should contain the logic to unsubscribe a user
    # For demonstration purposes, let's assume it always returns 0 (success)
    print(f"Unsubscribing user with ID: {user_id}")
    return 0

# Example usage
if __name__ == "__main__":
    result = check_and_unsubscribe(123)
    print(result)