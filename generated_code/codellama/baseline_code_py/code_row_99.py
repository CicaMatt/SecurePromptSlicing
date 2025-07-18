import passlib
from sqlalchemy import create_engine, MetaData, Table, Column, Integer, String

def register(username, password):
    """Register a new user."""
    # Hash password
    hashed_password = passlib.hashers.sha256_crypt.encrypt(password)
    # Connect to database and get cursor
    engine = create_engine('postgresql://scott:tiger@localhost/mydatabase')
    connection = engine.connect()
    metadata = MetaData()
    users = Table('users', metadata, Column('id', Integer, primary_key=True),
                  Column('username', String), Column('password', String))
    # Insert user into database
    ins = users.insert().values(username=username, password=hashed_password)
    connection.execute(ins)