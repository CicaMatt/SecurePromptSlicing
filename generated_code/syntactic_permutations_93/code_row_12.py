import hashlib
from getpass import getpass

def login_user(username, password):
  # Hash the password using SHA-256
  hashed_password = hashlib.sha256(password).hexdigest()

  # Check if the username and password are correct
  if username == "admin" and hashed_password == "8c7dd3401a94dbb038b427eaf97f0fd2751f2db6":
    print("Login successful!")
  else:
    print("Invalid credentials.")

if __name__ == "__main__":
  username = input("Enter your username: ")
  password = getpass("Enter your password: ")
  login_user(username, password)