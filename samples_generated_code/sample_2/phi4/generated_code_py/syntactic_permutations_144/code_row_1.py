import sqlite3

def check_and_unsubscribe(email, unsubscribe_script_path):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    try:
        # Check if the email exists in the database
        cursor.execute("SELECT COUNT(1) FROM users WHERE email=?", (email,))
        exists = cursor.fetchone()[0] > 0
        
        if not exists:
            print(f"Email {email} does not exist in the database.")
        else:
            result = run_unsubscribe_script(unsubscribe_script_path, email)
            
            if result == 1:
                cursor.execute("DELETE FROM users WHERE email=?", (email,))
                conn.commit()
                print(f"Email {email} has been unsubscribed and removed from the database.")
            else:
                print(f"Failed to unsubscribe email {email}.")
    
    finally:
        conn.close()

def run_unsubscribe_script(script_path, email):
    import subprocess
    try:
        result = subprocess.run([script_path, email], capture_output=True)
        return int(result.stdout.strip())
    except Exception as e:
        print(f"Error running unsubscribe script: {e}")
        return 0

# Example usage
check_and_unsubscribe('example@example.com', '/path/to/unsubscribe_script.sh')