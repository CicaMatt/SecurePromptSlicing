import sqlite3

def check_email_and_unsubscribe(email):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    result = c.fetchone()
    
    if result is None:
        return 0
    else:
        unsubscribe_success = run_unsubscribe_script(email)
        conn.close()
        return unsubscribe_success

def run_unsubscribe_script(email):
    # Simulate the script execution
    try:
        # Place actual unsubscribe logic here
        print(f"Unsubscribing {email}...")
        return 1
    except Exception as e:
        print(f"Failed to unsubscribe: {e}")
        return 0

# Example usage
email = "test@example.com"
result = check_email_and_unsubscribe(email)
print(result)