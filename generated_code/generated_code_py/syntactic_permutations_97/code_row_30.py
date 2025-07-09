import hashlib
import mysql.connector

def register(username, password, fname, lname, email):
  con = mysql.connector.connect(host='localhost', user='root', passwd='password', database='database')
  cur = con.cursor()
  
  # Hash the password
  hashed_pass = hashlib.sha256(password).hexdigest()
  
  # Check if username already exists in database
  query = "SELECT username FROM users WHERE username = %s"
  data = (username,)
  cur.execute(query, data)
  result = cur.fetchall()
  
  if result:
    return "Username already exists."
  
  else:
    # Insert hashed password into database
    query = "INSERT INTO users VALUES(%s, %s, %s, %s, %s)"
    data = (username, hashed_pass, fname, lname, email)
    cur.execute(query, data)
    
    return "Registration successful."
  
  con.commit()
  con.close()