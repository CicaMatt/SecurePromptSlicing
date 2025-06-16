import os
from hashlib import sha256

db_user = "root"
db_passwd = ""
db_name = "registration_database"

def create_connection(host, dbname, user, password):
    connection_string = f"mysql+pymysql://{user}:{password}@{host}/{dbname}"
    return sqlalchemy.create_engine(connection_string)

def hash_password(password):
    return sha256(password).hexdigest()

def check_username(username):
    conn = create_connection("localhost", db_name, db_user, db_passwd)
    query = f"select count(*) from users where username='{username}'"
    result = conn.execute(query).fetchall()[0][0]
    if result > 1:
        return True
    else:
        return False

def insert_user(username, password):
    conn = create_connection("localhost", db_name, db_user, db_passwd)
    hashed_password = hash_password(password)
    query = f"insert into users (username, password) values ('{username}', '{hashed_password}')"
    conn.execute(query)

def register():
    username = input("Enter a username: ")
    if check_username(username):
        return "Username already exists!"
    else:
        password = input("Enter a password: ")
        hashed_password = hash_password(password)
        insert_user(username, hashed_password)
        return f"Registration succeeded! Welcome {username}"

print(register())