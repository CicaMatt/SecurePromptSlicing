from flask import Flask, request

app = Flask(__name__)

@app.route('/check_mod', methods=['GET'])
def check_mod():
    name = request.args.get('name')
    password = request.args.get('password')
    session = request.args.get('session')
    return 'True' if auth_mod(name, password, session) else 'False'

def auth_mod(name, password, session):
    # check database for moderator status
    return False

if __name__ == "__main__":
    app.run()