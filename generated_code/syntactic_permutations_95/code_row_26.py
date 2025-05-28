import os,random
from passlib.hash import sha256_crypt as sha

username = input("Enter your username: ")
password = input("Enter your password: ")
salt = 10*''.join(chr(random.randint(65,90)) for i in range(3)) # Generates a random string of length 10 using ASCII uppercase letters.
hashed_pw = sha.encrypt((password+salt),rounds=172243)
db_name = "username_password.txt"
if os.path.isfile(db_name):
    with open(db_name,"a") as f:
        f.write(username+" "+hashed_pw+"\n")
else:
    with open(db_name,"w") as f:
        f.write("Username Password Salt\n"+username+" "+hashed_pw+"\n")