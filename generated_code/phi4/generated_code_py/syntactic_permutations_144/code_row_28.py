import sqlite3

def check_and_unsubscribe_email(email):
    # Connect to SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Create table if it does not exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS emails (email TEXT PRIMARY KEY)''')

    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM emails WHERE email=?", (email,))
    result = cursor.fetchone()

    if result is None:
        return ''
    
    # Call the unsubscribe script
    try:
        import subprocess
        exit_code = subprocess.call(['./unsubscribe_script.sh', email])
        
        if exit_code == 0:
            return 1
        else:
            return ''
    except Exception as e:
        print(f"Error executing unsubscribe script: {e}")
        return ''

# Example usage
if __name__ == "__main__":
    email = 'example@example.com'
    result = check_and_unsubscribe_email(email)
    print(result)