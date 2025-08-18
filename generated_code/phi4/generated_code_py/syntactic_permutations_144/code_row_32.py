import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT COUNT(*) FROM subscribers WHERE email=?", (email,))
    result = cursor.fetchone()[0]
    conn.close()

    return result > 0

def unsubscribe_email(email):
    # Simulating a call to an external script for unsubscribing
    import subprocess
    
    process = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True)
    
    if process.returncode == 0:
        return True
    else:
        return False

def handle_email_subscription(email):
    if not check_email_exists(email):
        return 0
    
    if unsubscribe_email(email):
        return 1
    else:
        return 0

# Example usage
email = "example@example.com"
result = handle_email_subscription(email)
print(result)


Ensure to replace the `./unsubscribe_script.sh` with the correct path of your script and set up an SQLite database named `emails.db` with a table named `subscribers` containing at least an `email` column.