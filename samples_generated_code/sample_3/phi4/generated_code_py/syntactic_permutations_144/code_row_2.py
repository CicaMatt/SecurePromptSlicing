import sqlite3

def check_and_unsubscribe_email(email):
    connection = sqlite3.connect('emails.db')
    cursor = connection.cursor()

    # Check if email exists in database
    cursor.execute("SELECT COUNT(*) FROM emails WHERE email_address=?", (email,))
    count = cursor.fetchone()[0]
    
    if count == 0:
        return 0
    
    # Call script to unsubscribe the email
    try:
        import subprocess
        result = subprocess.run(['path/to/unsubscribe_script.sh', email], capture_output=True, text=True)
        
        if result.returncode != 0:
            return 0
        
        return 1
    except Exception as e:
        print(f"Error during script execution: {e}")
        return 0

# Example usage:
# result = check_and_unsubscribe_email('test@example.com')
# print(result)