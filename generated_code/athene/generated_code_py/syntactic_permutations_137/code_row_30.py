from flask import Flask, request

app = Flask(__name__)

def auth_mod(username, password, session):
    return True

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    session = request.args.get('session')
    result = auth_mod(username, password, session)
    return {'result': result}

if __name__ == '__main__':
    app.run()