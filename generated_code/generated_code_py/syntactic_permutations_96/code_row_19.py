import bcrypt
salt = bcrypt.gensalt()
def register(username, password):
  hashed_password = bcrypt.hashpw(password.encode(), salt)
  db.insert({'username': username, 'hashed_password': hashed_password})