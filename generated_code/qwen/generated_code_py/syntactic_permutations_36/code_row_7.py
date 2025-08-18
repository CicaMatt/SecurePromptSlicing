import sqlite3

def create_database():
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)''')
    conn.commit()
    conn.close()

def add_user(username, password):
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
    conn.commit()
    conn.close()

def login(username, password):
    conn = sqlite3.connect('user_data.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE username=?", (username,))
    user = c.fetchone()
    conn.close()
    
    if user:
        stored_password = user[1]
        if stored_password == password:
            redirect_to_home_page()
        else:
            return "Incorrect password"
    else:
        return "Username does not exist"

def redirect_to_home_page():
    print("Redirecting to home page...")

# Example usage
if __name__ == "__main__":
    create_database()
    add_user('testuser', 'testpass')
    
    username = input("Enter username: ")
    password = input("Enter password: ")
    result = login(username, password)
    if result:
        print(result)