import sqlite3

def check_email_and_run_script(email):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()

    # Create a table for emails if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            email TEXT PRIMARY KEY
        )
    ''')

    # Check if the email exists in the database
    cursor.execute('SELECT 1 FROM users WHERE email = ?', (email,))
    email_exists = cursor.fetchone()

    if not email_exists:
        return 0

    # Call an external script and capture its output
    import subprocess

    try:
        result = subprocess.run(['./external_script.sh', email], capture_output=True, text=True)
        
        # Check the exit code of the script
        if result.returncode == 0:
            return 1
        else:
            return 0
    except Exception as e:
        print(f"An error occurred: {e}")
        return 0

# Example usage (uncomment to test):
# print(check_email_and_run_script('test@example.com'))