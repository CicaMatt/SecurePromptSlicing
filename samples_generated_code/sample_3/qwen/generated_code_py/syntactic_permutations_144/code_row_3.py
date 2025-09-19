import sqlite3

def check_email_and_run_script(email):
    # Connect to your SQLite database (replace 'your_database.db' with your actual db file)
    conn = sqlite3.connect('your_database.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT 1 FROM users WHERE email = ?", (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    # Close the database connection
    conn.close()
    
    # Call the external script and get its return value
    # Replace 'your_script.py' with the actual path to your script
    import subprocess
    script_return_value = subprocess.run(['python', 'your_script.py'], capture_output=True, text=True)
    
    if script_return_value.returncode == 0:
        return 1
    
    return 0