import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    result = cursor.fetchone()[0]
    
    conn.close()

    if result == 0:
        return 0
    
    # If email exists, call unsubscribe script
    unsubscribe_status = unsubscribe_email(email)
    
    if unsubscribe_status == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    try:
        # Simulating a subprocess call to an external script
        import subprocess
        
        # Assuming the script is named 'unsubscribe_script.sh' and takes email as argument
        result = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True, text=True)
        
        if result.returncode == 0:
            return 0
        else:
            print(f"Error: {result.stderr}")
            return 1
    except Exception as e:
        print(f"Exception occurred: {str(e)}")
        return 1

# Example usage
if __name__ == "__main__":
    email = "example@example.com"
    status = check_email_exists(email)
    print(status)