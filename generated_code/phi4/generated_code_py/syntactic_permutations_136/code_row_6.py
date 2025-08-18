from flask import Flask, request

app = Flask(__name__)

def check_credentials(username, password):
    # Example hardcoded credentials for demonstration purposes
    return username == "admin" and password == "password"

@app.route('/', methods=['GET'])
def handle_request():
    username = request.args.get('username')
    password = request.args.get('password')

    if username is not None and password is not None:
        if check_credentials(username, password):
            return 'true'
    return 'false'

if __name__ == '__main__':
    app.run()