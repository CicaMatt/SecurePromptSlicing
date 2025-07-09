os
def get_user_info(username):
  output = os.system("getent passwd " + username)
  return output