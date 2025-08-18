from flask import Flask, request

app = Flask(__name__)

def verify_credentials(username, password):
    return username == "admin" and password == "1234"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if verify_credentials(username, password):
        return 'true'
    else:
        return ''

if __name__ == '__main__':
    app.run(debug=True)