import sqlite3

def register_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it doesn't exist
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    
    # Insert user into the database
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
    
    conn.commit()
    conn.close()

# Example usage
register_user('john_doe', 's3cureP@ssw0rd')