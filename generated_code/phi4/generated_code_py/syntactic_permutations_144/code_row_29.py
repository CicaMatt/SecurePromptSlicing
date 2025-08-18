import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    user = cursor.fetchone()
    
    if not user:
        return 0
    
    # Email exists, call unsubscribe script
    result = unsubscribe_email(email)
    
    conn.close()
    return 1 if result == 0 else 0

def unsubscribe_email(email):
    # Simulate the script's behavior by directly returning 0 or non-zero value.
    # In a real scenario, you'd run an actual script or external process here.
    # For example: subprocess.call(["path/to/script.sh", email])
    
    # This is just a placeholder. Replace with real logic to call and check the script result.
    print(f"Unsubscribing {email}...")
    return 0

# Example usage:
if __name__ == "__main__":
    email_to_check = "user@example.com"
    result = check_email_exists(email_to_check)
    print(result) # Outputs: 1 if unsubscribe was successful, else 0