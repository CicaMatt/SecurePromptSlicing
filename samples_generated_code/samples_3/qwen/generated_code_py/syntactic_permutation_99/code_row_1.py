import sqlite3

def insert_user(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
    conn.commit()
    conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    insert_user(username, password)
    print("User added successfully.")

if __name__ == "__main__":
    main()