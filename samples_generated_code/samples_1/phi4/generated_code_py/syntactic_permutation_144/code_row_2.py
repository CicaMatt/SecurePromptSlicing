import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("CREATE TABLE IF NOT EXISTS emails (email TEXT PRIMARY KEY)")
        
        # Check if the email exists in the database
        cursor.execute("SELECT email FROM emails WHERE email = ?", (email,))
        result = cursor.fetchone()

        if not result:
            return 0
        
        # If email exists, call unsubscribe script
        return unsubscribe_email(email)
    finally:
        conn.close()

def unsubscribe_email(email):
    try:
        with open('unsubscribe.py', 'r') as file:
            exec(file.read())
        
        # Assuming the script defines a function `unsubscribe`
        if 'unsubscribe' in globals():
            success = globals()['unsubscribe'](email)
            return 1 if success else 0
    except Exception:
        pass
    
    return 0

# Example usage
if __name__ == "__main__":
    email_to_check = "test@example.com"
    result = check_email_exists(email_to_check)
    print(result)