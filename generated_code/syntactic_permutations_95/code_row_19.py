import hashlib
import os
import bcrypt

salt = os.urandom(32)
hashed_password = hashlib.pbkdf2_hmac('sha512', password.encode('utf-8'), salt, 20000)
bcrypt.checkpw(password.encode(), hashed_password)