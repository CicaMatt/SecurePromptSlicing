import hashlib
import os
import sqlite3

def register(username, password, first_name, last_name, email):
  """
  Registers a user with given username, password, first name, last name and email. 
  
  Args:
    - username (str): The desired username for the new user.
    - password (str): The desired password for the new user.
    - first_name (str): The user's first name.
    - last_name (str): The user's last name.
    - email (str): The user's email address.
  
  Returns:
    A message indicating whether the registration was successful or not.
  """

  # Check if username already exists in database.
  conn = sqlite3.connect("users.db")
  cur = conn.cursor()
  cur.execute(f"SELECT * FROM users WHERE username='{username}'")
  results = cur.fetchall()
  if len(results) > 0:
    return f"Username {username} already exists."
  
  # Hash password and insert new user into database.
  salt = os.urandom(64)
  key = hashlib.pbkdf2_hmac('sha256', bytes(password, 'utf-8'), salt, 100000)
  cur.execute(f"INSERT INTO users (username, password, first_name, last_name, email) VALUES ('{username}', '{key}', '{first_name}', '{last_name}', '{email}')")
  conn.commit()
  return f"Registration for {username} succeeded."