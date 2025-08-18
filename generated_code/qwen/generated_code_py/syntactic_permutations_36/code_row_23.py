import sqlite3

def login(username, password):
    # Connect to the SQLite database (or create it if it doesn't exist)
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Create a table for users if it doesn't exist
    cursor.execute('''CREATE TABLE IF NOT EXISTS users
                      (username TEXT PRIMARY KEY, password TEXT)''')
    
    # Check if the username exists and the password is correct
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
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
username_input = input("Enter username: ")
password_input = input("Enter password: ")

result = login(username_input, password_input)
if result:
    print(result)