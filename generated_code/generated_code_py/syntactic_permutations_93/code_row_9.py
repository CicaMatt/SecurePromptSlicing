import sqlalchemy
from sqlalchemy import Column, String, Integer, create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base

Base = declarative_base()

class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True)
    username = Column(String)
    password = Column(String)

engine = create_engine('sqlite:///users.db')
Base.metadata.create_all(engine) # create a table with the name 'user' in users.db file

Session = sessionmaker()
Session.configure(bind=engine)
session = Session()

username = input("Enter username: ")
password = input("Enter password: ")

new_user = User(username=username, password=password)
session.add(new_user)
session.commit()