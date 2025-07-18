import hashlib  # Hashing library
from sqlalchemy import create_engine, update, delete, select  # Database Library
from sqlalchemy.ext.declarative import declarative_base  # Base class for models
from sqlalchemy import Column, Integer, String  # Model column definitions
import bcrypt  # Password Hashing library

# Create a database engine and connection string
engine = create_engine("sqlite:///users.db")
Base = declarative_base()


class User(Base):
    __tablename__ = "user"
    id = Column(Integer, primary_key=True)
    username = Column(String(20), unique=True, nullable=False)
    password = Column(String(80), nullable=False)
    firstname = Column(String(50), nullable=False)
    lastname = Column(String(100), nullable=False)
    email = Column(String(256), unique=True, nullable=False)


def create_tables():
    Base.metadata.create_all(engine)


def add_user(username, password, firstname, lastname, email):
    # Hash the password
    hashed = bcrypt.hashpw(password.encode("utf8"), bcrypt.gensalt())

    # Create a new user instance and save it to database
    user = User(username=username, password=hashed, firstname=firstname, lastname=lastname, email=email)
    session.add(user)
    session.commit()
    return "Succeeded"