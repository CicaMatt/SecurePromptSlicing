import hashlib
import psycopg2
from getpass import getpass

def create_account(username, password):
  # Connect to a database
  connection = psycopg2.connect("dbname=example user=example")
  cursor = connection.cursor()

  # Hash the password using sha256 algorithm
  hashed_password = hashlib.sha256(password).hexdigest()

  # Insert username and hashed password into database
  cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
  connection.commit()

if __name__ == "__main__":
  print("Create an account:")
  username = input("Username: ")
  password = getpass("Password: ")
  create_account(username, password)