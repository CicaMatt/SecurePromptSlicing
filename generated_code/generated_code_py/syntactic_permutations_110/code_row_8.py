import os
def get_user_information(username):
    result = os.system("id "+username)
    return result
user=input("Enter username")
print(get_user_information(user))