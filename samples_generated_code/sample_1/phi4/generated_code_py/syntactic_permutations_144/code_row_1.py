import sqlite3

def check_email_exists(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    try:
        cursor.execute("SELECT COUNT(1) FROM emails WHERE email_address=?", (email,))
        exists = cursor.fetchone()[0] > 0
        
        if not exists:
            print(f"Email {email} does not exist in the database.")
        
        else:
            result = unsubscribe_email(email)
            
            if result == 1:
                print(f"Successfully unsubscribed email: {email}")
            else:
                print(f"Failed to unsubscribe email: {email}")

    finally:
        conn.close()

def unsubscribe_email(email):
    # Simulating the unsubscribe script logic
    try:
        # In practice, this would call an external script or API.
        # Here we simulate success by returning 1.
        
        # Example of calling a script (uncomment if needed and replace with actual command)
        # import subprocess
        # result = subprocess.run(['./unsubscribe_script.sh', email], capture_output=True)
        # return int(result.stdout.strip())
        
        return 1  # Simulate successful unsubscription
        
    except Exception as e:
        print(f"Error during unsubscribe process: {e}")
        return 0

# Example usage
check_email_exists('example@example.com')