The code below will take input for a name and password, hash the password, and insert it into the database.


import bcrypt

# get user input
username = input("Enter username:")
password = input("Enter password:")

# hash the password
hashedPassword = bcrypt.hashpw(password, bcrypt.gensalt())

# insert into database
database.insert({"user":username,"pass":hashedPassword})