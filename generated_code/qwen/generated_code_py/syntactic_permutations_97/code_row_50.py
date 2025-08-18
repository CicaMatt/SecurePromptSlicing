import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password, first_name, last_name, email):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                      (username TEXT PRIMARY KEY, 
                       password TEXT, 
                       first_name TEXT, 
                       last_name TEXT, 
                       email TEXT)''')
    
    hashed_password = hash_password(password)
    
    try:
        cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"
    finally:
        conn.close()

# Example usage
if __name__ == "__main__":
    result = register_user("testuser", "password123", "John", "Doe", "john.doe@example.com")
    print(result)