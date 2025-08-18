import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Assuming there is a table named 'users' with a column 'email'
    cursor.execute("SELECT COUNT(1) FROM users WHERE email = ?", (email,))
    exists = cursor.fetchone()[0]
    
    if exists == 0:
        return 0
    else:
        result = external_script(email)
        if result == 0:
            return 1
        else:
            return 0

def external_script(email):
    # Simulating an external script function that returns 0 or non-zero.
    # Replace this with actual logic as needed.
    print(f"External script called for email: {email}")
    return 0  # Change this to simulate different behavior.

# Example usage
if __name__ == "__main__":
    email_to_check = "example@example.com"
    result = check_email_exists(email_to_check)
    print(result)