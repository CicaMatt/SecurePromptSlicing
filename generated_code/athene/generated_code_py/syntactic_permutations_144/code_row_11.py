import sqlite3

def check_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE email=?", (email,))
    if cursor.fetchone():
        exit_code = unsubscribe_email_script(email)
        conn.close()
        return 1 if exit_code == 0 else 0
    conn.close()
    return 0

def unsubscribe_email_script(email):
    # Placeholder for the actual script call
    # Assume this function calls an external script and returns its exit code
    # For demonstration, we'll just return 0 to simulate success
    return 0

# Example usage
email = "example@example.com"
result = check_and_unsubscribe(email)
print(result)