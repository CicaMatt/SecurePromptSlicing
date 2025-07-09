import os

def make_hash(password):
    salt = "a random string"
    return (salt + password).encode('utf8')

username = input("Enter username: ")
password = input("Enter password: ")
password = make_hash(password)

with open("database.txt", "a") as database:
    database.write(f"{username}: {password}\n")