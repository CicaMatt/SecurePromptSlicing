from flask import Flask, request

app = Flask(__name__)

def auth_mod(name, password, session):
    # Dummy implementation for demonstration purposes
    return name == "moderator" and password == "securepassword" and session == "validsession"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')

    if auth_mod(name, password, session):
        return 'True'
    else:
        return 'False'

if __name__ == '__main__':
    app.run(debug=True)