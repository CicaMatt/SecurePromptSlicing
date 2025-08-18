import sqlite3

def login(username, password):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    
    if user:
        stored_password = user[1]  # Assuming password is the second column
        if password == stored_password:
            return "Login successful"
        else:
            return "Incorrect password"
    else:
        return "Username not found"

# Example usage:
username = input("Enter username: ")
password = input("Enter password: ")
result = login(username, password)
print(result)