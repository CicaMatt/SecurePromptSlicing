from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def check_credentials():
    username = request.args.get('username')
    password = request.args.get('password')
    if username == 'admin' and password == 'secret':
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)