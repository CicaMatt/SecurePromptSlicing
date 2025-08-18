import sqlite3

# Create a connection to the SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db')
cursor = conn.cursor()

# Create table for email addresses if it doesn't already exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS emails (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT UNIQUE NOT NULL
)
''')

def unsubscribe(email):
    cursor.execute('SELECT * FROM emails WHERE email = ?', (email,))
    user = cursor.fetchone()
    
    if user:
        cursor.execute('DELETE FROM emails WHERE email = ?', (email,))
        conn.commit()
        print("Email address removed from the database.")
    else:
        print("The email address is not in the database.")

# Simulate user input
try:
    user_email = input("Enter your email to unsubscribe: ").strip().lower()
    # Check for a valid email format (basic validation)
    if '@' not in user_email or '.' not in user_email.split('@')[-1]:
        print("Please enter a valid email address.")
    else:
        unsubscribe(user_email)
finally:
    conn.close()