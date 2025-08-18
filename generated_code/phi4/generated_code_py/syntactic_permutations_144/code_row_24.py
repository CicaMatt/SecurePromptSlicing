import sqlite3

def check_and_unsubscribe(user_id, db_path=':memory:', unsubscribe_script_path='unsubscribe.py'):
    # Connect to the database
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    try:
        # Check if user exists in the database
        cursor.execute("SELECT 1 FROM users WHERE id = ?", (user_id,))
        result = cursor.fetchone()

        if not result:
            return 0
        
        # User exists, call the unsubscribe script
        import subprocess
        process = subprocess.run(['python', unsubscribe_script_path, str(user_id)], capture_output=True)
        
        # Check the output of the script
        if process.returncode == 0 and process.stdout.strip() == b'0':
            return 1
        
    finally:
        conn.close()

    return 0

# Example usage (assuming the necessary database and script are set up):
# result = check_and_unsubscribe(123)
# print(result)