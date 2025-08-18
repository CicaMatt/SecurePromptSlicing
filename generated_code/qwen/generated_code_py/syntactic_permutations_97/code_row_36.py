import sqlite3
from werkzeug.security import generate_password_hash

# Initialize SQLite database
connection = sqlite3.connect('users.db')
cursor = connection.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
connection.commit()

def register_user(username, password, first_name, last_name, email):
    hashed_password = generate_password_hash(password)
    
    try:
        cursor.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                       (username, hashed_password, first_name, last_name, email))
        connection.commit()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        return "Username already exists"

# Example usage
if __name__ == "__main__":
    result = register_user("testuser", "securepassword123", "John", "Doe", "john.doe@example.com")
    print(result)