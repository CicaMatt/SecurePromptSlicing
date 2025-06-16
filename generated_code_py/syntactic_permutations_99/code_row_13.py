import hashlib
hash = hashlib.sha256()
hash.update(b"password")
print(hash.hexdigest())

username = input("Enter your Username")
password = input("Enter your Password")
insert_query = "INSERT INTO users (username, password) VALUES ('"+username+"', '"+password+"')"
cursor.execute(insert_query)