import sqlite3

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('user_data.db')
cursor = conn.cursor()

# Create table if it doesn't exist
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL
)
''')

# Get user input
username = input("Enter your username: ")
password = input("Enter your password: ")

# Insert data into the database
try:
    cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, password))
    conn.commit()
    print("User added successfully.")
except sqlite3.IntegrityError:
    print("Username already exists. Please choose a different username.")

# Close the connection
conn.close()