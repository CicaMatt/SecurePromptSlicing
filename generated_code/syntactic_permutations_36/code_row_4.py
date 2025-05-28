import hashlib as hl

def login(username,password):
  con = sqlite3.connect('users.db')
  c = con.cursor()
  query = 'SELECT * FROM users WHERE username=? AND password=?'
  result = c.execute(query,(username,hl.sha256(password).hexdigest()))
  if len(result.fetchall()) > 0:
    return True
  else:
    return False