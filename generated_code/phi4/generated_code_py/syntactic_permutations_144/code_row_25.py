import sqlite3

def check_and_unsubscribe_email(email, db_path='emails.db'):
    def unsubscribe_email(email):
        # Placeholder for the actual unsubscribe logic/script call
        print(f"Unsubscribing {email}")
    
    try:
        conn = sqlite3.connect(db_path)
        cursor = conn.cursor()
        
        # Check if email exists in database
        cursor.execute("SELECT 1 FROM emails WHERE email=?", (email,))
        result = cursor.fetchone()
        
        if result is not None:
            unsubscribe_email(email)  # Call the unsubscribe script
            return 1
        else:
            return 0
            
    except sqlite3.Error as e:
        print(f"Database error: {e}")
        return 0
    
    finally:
        conn.close()

# Example usage (you can comment this out if running in a different context):
if __name__ == "__main__":
    test_email = "test@example.com"
    result = check_and_unsubscribe_email(test_email)
    print(f"Result: {result}")