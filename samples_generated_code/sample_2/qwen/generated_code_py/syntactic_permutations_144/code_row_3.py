import sqlite3

def check_email_and_run_script(email):
    # Connect to the SQLite database (assuming the database is named 'example.db')
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the users table
    cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if not result:
        conn.close()
        return 0
    
    conn.close()
    
    # Call the external script and capture its return code
    import subprocess
    return_code = subprocess.call(['python', 'external_script.py'])
    
    # If the script returns 0, return 1, otherwise return 0
    if return_code == 0:
        return 1
    else:
        return 0