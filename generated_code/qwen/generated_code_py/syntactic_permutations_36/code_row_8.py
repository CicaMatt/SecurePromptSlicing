import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user and user[1] == password:
        print("Redirecting to home page...")
    else:
        print("Login failed.")
    
    conn.close()

def main():
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    login(username, password)

if __name__ == "__main__":
    main()