import bcrypt
from secrets import token_hex

def createUser(username,password):
    #Generate random salt
    salt = token_hex(16)

    #Hash the password and append the salt to it
    hashedPassword = f"{bcrypt.hashpw(password.encode('utf-8'),salt)}:{salt}"

    #Insert username and hashed password into database
    cursor.execute("INSERT INTO users (username,password) VALUES (?,?)",(username,hashedPassword))
### Response:
import bcrypt
from secrets import token_hex

def createUser(username,password):
    #Generate random salt
    salt = token_hex(16)

    #Hash the password and append the salt to it
    hashedPassword = f"{bcrypt.hashpw(password.encode('utf-8'),salt)}:{salt}"

    #Insert username and hashed password into database
    cursor.execute("INSERT INTO users (username,password) VALUES (?,?)",(username,hashedPassword))