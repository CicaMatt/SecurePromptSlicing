def check_mod(username,password):
    if username=='admin' and password =='admin':
        return 'true'
    else :
        return 'false'
if __name__ == "__main__":
    check_mod('admin','admin')