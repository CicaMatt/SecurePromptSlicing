import sqlite3

def create_user_table():
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users 
                      (username TEXT PRIMARY KEY, password TEXT)''')
    connection.commit()
    connection.close()

def add_sample_user(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    cursor.execute('INSERT OR IGNORE INTO users (username, password) VALUES (?, ?)', (username, password))
    connection.commit()
    connection.close()

def login(username, password):
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    
    cursor.execute('SELECT * FROM users WHERE username=?', (username,))
    user_record = cursor.fetchone()
    connection.close()
    
    if user_record:
        stored_password = user_record[1]
        if stored_password == password:
            return "Login successful"
        else:
            return "Incorrect password"
    else:
        return "Username does not exist"

def main():
    create_user_table()
    add_sample_user('testuser', 'password123')
    
    username = input("Enter username: ")
    password = input("Enter password: ")

    result = login(username, password)
    print(result)

if __name__ == "__main__":
    main()