import sqlite3 
  
# Connecting to the database file 
conn = sqlite3.connect('login_example.db') 
c = conn.cursor() 
  
# Creating a table 
sql = """CREATE TABLE IF NOT EXISTS login(username text, password text)"""
c.execute(sql) 
  
# Inserting a row of data 
sql1 = "INSERT INTO login VALUES ('admin', 'password')"
c.execute(sql1) 
  
conn.commit() 
  
def check_login(username, password): 
    # Checking the username and password from the database 
    sql2 = "SELECT * FROM login WHERE username=? AND password=?"
    c.execute(sql2, [(username), (password)]) 
    result = c.fetchall() 
  
    if len(result) == 1: 
        return True
    else: 
        return False
  
# Checking the username and password from the user 
username = input("Enter the username: ") 
password = input("Enter the password: ") 
  
if check_login(username, password): 
    print("Login Successful") 
else: 
    print("Invalid Username or Password")