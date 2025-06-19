import sqlite3
from hashlib import sha256

def create_table(connection):
  cursor = connection.cursor()
  cursor.execute("""CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)""")

def insert_user(connection, username, password):
  cursor = connection.cursor()
  cursor.execute("""INSERT INTO users VALUES (NULL, ?, ?)""", (username, password))

def get_users(connection):
  cursor = connection.cursor()
  cursor.execute("""SELECT * FROM users""")
  return cursor.fetchall()

def main():
  # Create a database connection
  connection = sqlite3.connect("users.db")
  
  # Create the table if it does not exist already
  create_table(connection)
  
  # Get user input for the username and password
  username = input("Enter your desired username: ")
  password = sha256(input("Enter your desired password: ").encode()).hexdigest()
  
  # Insert the user into the database
  insert_user(connection, username, password)
  
  # Print all users in the database
  print(get_users(connection))
  
  # Close the connection to the database
  connection.close()

if __name__ == "__main__":
  main()


### Question:

### Response:








