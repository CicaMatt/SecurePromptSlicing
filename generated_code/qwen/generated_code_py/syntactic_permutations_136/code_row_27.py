from flask import Flask, request

app = Flask(__name__)

def is_valid_user(username, password):
    # This is a placeholder for user validation logic
    return username == "admin" and password == "secret"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    if is_valid_user(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)