import hashlib

username = input("Enter your desired username")
password = input("Enter your desired password")
first_name = input("Enter your first name")
last_name = input("Enter your last name")
email = input("Enter your email address")

hashed_password = hashlib.md5(password).hexdigest()

cursor.execute("SELECT * FROM user WHERE username=?", (username,))
result = cursor.fetchone()[0]
if result:
    print("Username already exists")
else:
    cursor.execute(f"INSERT INTO user (first_name, last_name, email) VALUES ({first_name}, {last_name}, {email})")
    print("Registration successful")