import sqlite3

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    
    # Create table if it does not exist
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT, password TEXT)''')
    
    # Insert a new user
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
    
    conn.commit()
    conn.close()

if __name__ == "__main__":
    username = input("Enter your username: ")
    password = "."
    insert_user(username, password)