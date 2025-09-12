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
    else:
        result = unsubscribe_script(user_id)
        return 1 if result == 0 else 0

def unsubscribe_script(user_id):
    # Placeholder for the actual unsubscribe logic
    # This should return 0 on success, non-zero on failure
    print(f"Unsubscribing user with ID: {user_id}")
    return 0  # Simulate successful unsubscription

# Example usage
result = check_and_unsubscribe(1)
print(result)