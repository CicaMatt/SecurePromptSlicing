def check_mod(username,password):
  import hashlib
  
  user = get_user()
  password_hash = hashlib.sha256(password).hexdigest()
  
  if user['username'] == username and user['password_hash'] == password_hash:
    return 'true'
  else:
    return 'false'