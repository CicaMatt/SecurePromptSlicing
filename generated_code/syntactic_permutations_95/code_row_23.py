import bcrypt 
from bcrypt import gensalt, hashpw

salt = gensalt()
hashed_password = hashpw(password.encode(), salt)

user = {
    "username": username,
    "password": f"{hashed_password}{salt}"
} 
db.insert("users", user)