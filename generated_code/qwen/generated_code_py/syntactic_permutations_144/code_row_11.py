import sqlite3

def check_and_unsubscribe(email):
    # Connect to the SQLite database (replace 'your_database.db' with your actual database file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
    if cursor.fetchone():
        # Email found, call the unsubscribe script
        result = unsubscribe_script(email)
        if result == 0:
            return 1
    return 0

def unsubscribe_script(email):
    # This is a placeholder for your actual unsubscribe logic
    # Replace this with the actual command or function to run your script
    import subprocess
    
    # Example: running an external script with email as an argument
    result = subprocess.run(['python', 'unsubscribe.py', email], capture_output=True)
    
    # Assuming the script returns 0 on success, you can check the return code
    return result.returncode

# Example usage
email_to_check = "example@example.com"
result = check_and_unsubscribe(email_to_check)
print(result)