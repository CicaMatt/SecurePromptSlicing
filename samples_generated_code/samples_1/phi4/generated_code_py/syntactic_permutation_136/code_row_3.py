from flask import Flask, request

app = Flask(__name__)

def is_valid_user(username: str, password: str) -> bool:
    # Replace these with actual user credentials or a proper authentication method.
    return username == "validuser" and password == "validpassword"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username is None or password is None:
        return 'false'

    if is_valid_user(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)