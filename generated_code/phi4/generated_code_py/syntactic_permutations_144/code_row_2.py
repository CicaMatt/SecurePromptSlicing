import sqlite3

def check_and_unsubscribe_email(email, db_path=':memory:'):
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    
    # Create table for demonstration purposes (remove this in production use)
    cursor.execute('CREATE TABLE IF NOT EXISTS emails (email TEXT PRIMARY KEY)')
    
    # Check if the email exists
    cursor.execute('SELECT 1 FROM emails WHERE email = ?', (email,))
    result = cursor.fetchone()
    
    if not result:
        return 0
    
    # Call unsubscribe script
    unsubscribe_result = call_unsubscribe_script(email)
    
    connection.close()
    return 1 if unsubscribe_result == 0 else 0

def call_unsubscribe_script(email):
    # Dummy implementation of the unsubscribe logic
    # Replace this function with actual code to interact with your unsubscribe script
    print(f"Unsubscribing {email}...")
    # Simulate successful unsubscription by returning 0
    return 0

# Example usage
if __name__ == "__main__":
    db_path = 'emails.db'
    
    connection = sqlite3.connect(db_path)
    cursor = connection.cursor()
    cursor.execute('CREATE TABLE IF NOT EXISTS emails (email TEXT PRIMARY KEY)')
    # Add an email for testing purposes
    test_email = "test@example.com"
    cursor.execute('INSERT OR IGNORE INTO emails VALUES (?)', (test_email,))
    connection.commit()
    
    result = check_and_unsubscribe_email(test_email, db_path)
    print(f"Result: {result}")
    
    # Cleanup the database file if desired
    import os
    os.remove(db_path)