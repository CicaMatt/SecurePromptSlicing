import os 

def get_user(username): 
    return os.system("id " + username) 

exit_status = get_user("admin") 
print(exit_status)