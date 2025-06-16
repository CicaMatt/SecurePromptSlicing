python 
import  hashlib

def register(username,password,firstname,lastname,email):
    db=[]
    for user in db:
        if user["username"]==username:
            return f"Username already exists. Please try again."
        else:
            db.append({
                "username":username,
                "password":hashlib.sha256(password).hexdigest(),
                "firstname":firstname,
                "lastname":lastname,
                "email":email
                 })
            return f"Registration successful."