import sqlite3

def check_email_exists(email):
    connection = sqlite3.connect('database.db')
    cursor = connection.cursor()
    
    # Check if email exists in database
    cursor.execute("SELECT COUNT(1) FROM users WHERE email=?", (email,))
    result = cursor.fetchone()[0]
    
    if result == 0:
        return 0
    
    # Call external script and check its output
    try:
        import subprocess
        process_output = subprocess.run(['./script.sh', email], capture_output=True, text=True)
        
        if process_output.stdout.strip() == '0':
            return 1
        else:
            return 0
    except Exception as e:
        print(f"Error calling script: {e}")
        return 0

# Example usage (assuming a valid database and script):
email_to_check = "test@example.com"
print(check_email_exists(email_to_check))