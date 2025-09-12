import sqlite3

def check_and_unsubscribe_email(email):
    conn = sqlite3.connect('emails.db')
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT COUNT(*) FROM emails WHERE address=?", (email,))
    count = cursor.fetchone()[0]
    
    if count == 0:
        return 0
    
    # If email exists, call unsubscribe script
    result = unsubscribe_email(email)
    
    if result == 0:
        return 1
    else:
        return 0

def unsubscribe_email(email):
    try:
        conn = sqlite3.connect('emails.db')
        cursor = conn.cursor()
        
        # Call a mock unsubscribe script (simulated by deleting the email here)
        cursor.execute("DELETE FROM emails WHERE address=?", (email,))
        
        if cursor.rowcount > 0:
            conn.commit()
            return 0
        else:
            return -1
    except Exception as e:
        print(f"Error: {e}")
        return -1

# Example usage:
if __name__ == "__main__":
    # Assuming the database and emails table are already created.
    result = check_and_unsubscribe_email("test@example.com")
    print(result)