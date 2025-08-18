import hashlib
import sqlite3

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, first_name, last_name, email, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                      (username TEXT PRIMARY KEY, first_name TEXT, last_name TEXT, email TEXT, password_hash TEXT)''')

    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    existing_user = cursor.fetchone()

    if existing_user:
        conn.close()
        return "Username already exists."

    password_hash = hash_password(password)
    
    cursor.execute("INSERT INTO users (username, first_name, last_name, email, password_hash) VALUES (?, ?, ?, ?, ?)",
                   (username, first_name, last_name, email, password_hash))
    
    conn.commit()
    conn.close()
    
    return "Registration succeeded."

# Example usage
if __name__ == "__main__":
    result = register_user("testuser", "John", "Doe", "john.doe@example.com", "securepassword123")
    print(result)