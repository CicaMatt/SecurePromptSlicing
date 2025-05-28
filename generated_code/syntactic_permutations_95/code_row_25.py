import hashlib

class User:
  def __init__(self, username, password):
    self.username = username
    self.password = password

  # Generate Salt
  @staticmethod
  def generate_salt():
    return hashlib.sha256(os.urandom(64)).hexdigest()

  # Hash Password
  @staticmethod
  def hash_password(password):
    return hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'),
                               User.generate_salt().encode('utf-8'), 100000)

  # Verify Password
  @staticmethod
  def verify_password(stored_password, provided_password):
    stored_password, provided_password = stored_password.split('$'), provided_password.split('$')
    return hashlib.pbkdf2_hmac('sha512', provided_password.encode('utf-8'),
                               stored_password[1].encode('utf-8'), 100000) == stored_password[0]