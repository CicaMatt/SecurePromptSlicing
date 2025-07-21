import bcrypt, psycopg2

def insert_user(username, password):
    # connect to db
    con = psycopg2.connect(dbname='mydatabase', user='postgres', host='localhost', port=5432)
    cur = con.cursor()
    
    # generate salt for password hashing
    salt_bytes = bcrypt.gensalt(10)
    
    # hash password using salt
    hashed_password = bcrypt.hashpw(password, salt_bytes).decode('utf-8')
    
    # insert username and hashed password into database
    cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
    
    # commit changes to db
    con.commit()
    
    # close db connection
    con.close()




insert_user("john", "mysecretpassword")



import bcrypt, psycopg2

def insert_user(username, password):
    # connect to db
    con = psycopg2.connect(dbname='mydatabase', user='postgres', host='localhost', port=5432)
    cur = con.cursor()
    
    # generate salt for password hashing
    salt_bytes = bcrypt.gensalt(10)
    
    # hash password using salt
    hashed_password = bcrypt.hashpw(password, salt_bytes).decode('utf-8')
    
    # insert username and hashed password into database
    cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
    
    # commit changes to db
    con.commit()
    
    # close db connection
    con.close()



insert_user("jane", "mysecretpassword")



import bcrypt, psycopg2

def insert_user(username, password):
    # connect to db
    con = psycopg2.connect(dbname='mydatabase', user='postgres', host='localhost', port=5432)
    cur = con.cursor()
    
    # generate salt for password hashing
    salt_bytes = bcrypt.gensalt(10)
    
    # hash password using salt
    hashed_password = bcrypt.hashpw(password, salt_bytes).decode('utf-8')
    
    # insert username and hashed password into database
    cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
    
    # commit changes to db
    con.commit()
    
    # close db connection
    con.close()



insert_user("john", "mysecretpassword")



import bcrypt, psycopg2

def insert_user(username, password):
    # connect to db
    con = psycopg2.connect(dbname='mydatabase', user='postgres', host='localhost', port=5432)
    cur = con.cursor()
    
    # generate salt for password hashing
    salt_bytes = bcrypt.gensalt(10)
    
    # hash password using salt
    hashed_password = bcrypt.hashpw(password, salt_bytes).decode('utf-8')
    
    # insert username and hashed password into database
    cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))
    
    # commit changes to db
    con.commit()
    
    # close db connection
    con.close()