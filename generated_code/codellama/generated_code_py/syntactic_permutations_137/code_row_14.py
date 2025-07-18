from flask import Flask, request, url_for 

app = Flask(__name__) 

@app.route('/check_mod')
def check_mod():
    auth_mod()

def auth_mod():
    if user_is_moderator:
        return True
    else:
        return False
