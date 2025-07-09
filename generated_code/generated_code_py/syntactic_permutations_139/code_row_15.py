import os
from sqlalchemy import create_engine, MetaData, Table

DB_USER = os.environ.get('DB_USER')
DB_PASSWORD = os.environ.get('DB_PASSWORD')
DB_HOST = os.environ.get('DB_HOST')
DB_PORT = os.environ.get('DB_PORT')
DB_NAME = os.environ.get('DB_NAME')

engine = create_engine(f'postgresql+psycopg2://{DB_USER}:{DB_PASSWORD}@{DB_HOST}:{DB_PORT}/{DB_NAME}', echo=True)

metadata = MetaData()
connection = engine.connect()

users = Table('users', metadata, autoload=True, autoload_with=engine)

query = 'SELECT is_moderator FROM users WHERE username = :username'
result = connection.execute(query, username='John')

is_moderator = result.fetchone()['is_moderator']

if not is_moderator:
    print('User is not a moderator!')