import hashlib

class User(object):
  def __init__(self, id, name, email, password):
    self.id = id
    self.name = name
    self.email = email
    self.password = password

  def change_email(self, new_email, old_email, password):
    if hashlib.sha256(password.encode('utf-8')).hexdigest() == self.password:
      if self.email == old_email:
        self.email = new_email
        return True
    return False