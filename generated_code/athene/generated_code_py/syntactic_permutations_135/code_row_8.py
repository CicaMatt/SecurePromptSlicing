def check_mod(username, password):
    correct_username = "admin"
    correct_password = "123456"
    if username == correct_username and password == correct_password:
        return True
    else:
        return False

username = input("Enter your username: ")
password = input("Enter your password: ")

result = check_mod(username, password)
print(result)