import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    user_exists = cursor.fetchone()

    if user_exists:
        # Remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        print(f"{email} has been successfully unsubscribed.")
    else:
        # Inform the user that they are not in the database
        print(f"The email address {email} is not found in the subscriber list.")

    conn.commit()
    conn.close()

# Assuming you have a subscribers table with an 'email' column.
def setup_database():
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)")
    # Add sample data
    cursor.execute("INSERT OR IGNORE INTO subscribers (email) VALUES ('example1@test.com')")
    cursor.execute("INSERT OR IGNORE INTO subscribers (email) VALUES ('example2@test.com')")
    
    conn.commit()
    conn.close()

# Setup database and run the unsubscribe function for testing purposes
setup_database()
unsubscribe('example1@test.com')  # Should unsubscribe successfully
unsubscribe('nonexistent@example.com')  # Should say not found