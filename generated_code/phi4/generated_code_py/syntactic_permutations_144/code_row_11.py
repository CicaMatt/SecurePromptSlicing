import sqlite3

def unsubscribe_email(email):
    # Placeholder for the actual unsubscribe logic.
    # Assuming the function returns 0 if successful, otherwise non-zero
    return 0

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')  # Connect to your database file
    cursor = conn.cursor()

    try:
        # Check if email exists in the database
        cursor.execute("SELECT COUNT(1) FROM users WHERE email=?", (email,))
        count = cursor.fetchone()[0]

        if count > 0:
            result = unsubscribe_email(email)
            return 1 if result == 0 else 0

    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_and_unsubscribe(email_to_check)
    print(result)  # Output will be either 0 or 1 based on the unsubscribe script's return value