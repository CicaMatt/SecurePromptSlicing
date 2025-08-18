import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT COUNT(*) FROM emails WHERE email_address = ?", (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    
    # Call the unsubscribe script
    return unsubscribe_email(email)

def unsubscribe_email(email):
    try:
        # Simulate calling an external script
        success = call_unsubscribe_script(email)
        return 1 if success else 0
    except Exception as e:
        print(f"Error during unsubscription: {e}")
        return 0

def call_unsubscribe_script(email):
    # Dummy implementation of the unsubscribe process
    # In a real-world scenario, this would involve calling an external script or API
    # Here we simulate it always succeeds for demonstration purposes
    return True

# Example usage:
email_to_check = "example@example.com"
result = check_email_exists(email_to_check)
print(result)

# To make the above code runnable in an actual environment, ensure you have a SQLite database named 'database.db'
# with a table `emails` and a column `email_address`.