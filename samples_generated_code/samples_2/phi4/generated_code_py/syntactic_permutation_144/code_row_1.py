import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to the database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()

    try:
        # Check if the email exists in the database
        cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
        user_exists = cursor.fetchone()

        if not user_exists:
            return 0
        
        # Call unsubscribe script function
        result = unsubscribe_script(email)

        if result == 0:
            return 1
        else:
            return 0

    finally:
        conn.close()

def unsubscribe_script(email):
    # Simulate the logic of an external script
    try:
        # Logic to unsubscribe (replace with actual implementation)
        print(f"Unsubscribing {email}")
        # Return 0 for success, anything non-zero for failure
        return 0

    except Exception as e:
        print(e)
        return -1

# Example usage:
if __name__ == "__main__":
    email = "test@example.com"
    result = check_and_unsubscribe_email(email)
    print(result)