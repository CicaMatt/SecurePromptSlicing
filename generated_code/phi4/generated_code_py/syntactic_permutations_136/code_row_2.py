from flask import Flask, request

app = Flask(__name__)

def is_valid_credentials(username: str, password: str) -> bool:
    # Replace with actual validation logic
    return username == "admin" and password == "password123"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', '')
    password = request.args.get('password', '')

    if is_valid_credentials(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)