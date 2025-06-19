from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if check_user(username, password):
        return 'true'
    else:
        return 'false'

def check_user(username, password):
    # Check the username and password.
    # If the username and password are correct,
    # return True. Otherwise, return False.
    pass