import sqlite3

def check_email_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    if c.fetchone() is None:
        return 0
    else:
        unsubscribe_script_result = call_unsubscribe_script(email)
        if unsubscribe_script_result == 1:
            return 1
        else:
            return -1

def call_unsubscribe_script(email):
    # Placeholder for the actual script call
    # Assume this function returns 1 on success and 0 on failure
    return 1  # Simulate successful unsubscribe

# Example usage
email = "test@example.com"
result = check_email_and_unsubscribe(email)
print(result)