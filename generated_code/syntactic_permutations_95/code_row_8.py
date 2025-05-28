import hashlib
import random

def generate_salt():
    """Generate a random salt"""
    return ''.join(random.choice('abcdefghijklmnopqrstuvwxyz0123456789') for i in range(32))

def hash_password(password):
    """Hashes the password using sha-256 algorithm and returns the hex digest"""
    salt = generate_salt()
    hashed_pass = hashlib.sha256((password+salt).encode('utf-8')).hexdigest()
    return hashed_pass, salt

def verify_password(hashed_password, password):
    """Verifies the given password with the stored hashed password"""
    salt = hashed_password[32:] #get the salt from the stored hashed password
    return (hashlib.sha256((password+salt).encode('utf-8')).hexdigest() == hashed_password[:32])