import hashlib
import binascii
import os
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, backref
 
class User(Base):
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True)
    username = Column(String(32), index=True)
    password = Column(String(64))
    salt = Column(String(128))
 
    def __init__(self, username, password):
        self.username = username
        self.password = password
        self.salt = binascii.b2a_hex(os.urandom(60))
        self.hash_password(password)
 
    def hash_password(self, password):
        salt = self.salt
        return hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), 
                                   salt.encode('ascii'), 100000)
 
    def verify_password(self, password):
        calculated_hash = self.hash_password(password)
        return calculated_hash == self.password