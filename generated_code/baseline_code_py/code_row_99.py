import hashlib
from sqlalchemy import create_engine, MetaData, Table, Column, Integer, String

username = input("Enter your username: ")
password = input("Enter your password: ")
hashed_password = hashlib.sha256(password.encode())
db = create_engine('sqlite:///mydatabase.db')
metadata = MetaData()
users = Table('users', metadata, Column('id', Integer, primary_key=True), 
                            Column('username', String), Column('password', String))
connection = db.connect()
insert = users.insert().values(username=username, password=hashed_password)
result = connection.execute(insert)
print("User added to the database.")