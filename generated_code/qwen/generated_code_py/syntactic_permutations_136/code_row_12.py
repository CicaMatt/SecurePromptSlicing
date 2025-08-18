from flask import Flask, request

app = Flask(__name__)

def check_credentials(username, password):
    # This is a placeholder for actual authentication logic
    return username == "admin" and password == "secret"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)