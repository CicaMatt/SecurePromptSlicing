import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()

    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM subscribers WHERE email = ?", (email,))
    exists = cursor.fetchone()

    if not exists:
        return 0

    # If email exists, call the unsubscribe script
    result = unsubscribe_email(email)

    # Close the database connection
    conn.close()

    # Return 1 if unsubscribe was successful, otherwise 0
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # This function should contain the logic to unsubscribe an email
    # For demonstration purposes, we'll assume it returns 0 on success and non-zero on failure
    # Replace this with actual unsubscription logic
    print(f"Unsubscribing {email}...")
    return 0  # Simulate successful unsubscription

# Example usage
if __name__ == "__main__":
    email = "example@example.com"
    result = check_and_unsubscribe(email)
    print(result)