import hashlib
import sqlite3

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    
    hashed_password = hashlib.sha256(password.encode()).hexdigest()
    
    try:
        c.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)", 
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"
    finally:
        conn.close()

# Example usage
print(register_user('testuser', 'securepassword123', 'John', 'Doe', 'john.doe@example.com'))