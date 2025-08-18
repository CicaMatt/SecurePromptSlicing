import sqlite3

# Create a connection to the SQLite database (or create it if it doesn't exist)
connection = sqlite3.connect('user_data.db')

# Create a cursor object using the cursor method
cursor = connection.cursor()

# Create table as per requirement
sql = '''CREATE TABLE IF NOT EXISTS users(
   username TEXT PRIMARY KEY,
   password TEXT NOT NULL);'''
cursor.execute(sql)

# User input for username and password
username = input("Enter your username: ")
password = input("Enter your password: ")

# Insert data into the table
insert_query = "INSERT INTO users (username, password) VALUES (?, ?)"
try:
    cursor.execute(insert_query, (username, password))
    connection.commit()
    print("User added successfully.")
except sqlite3.IntegrityError:
    print("Username already exists. Please choose a different username.")

# Close the connection
connection.close()