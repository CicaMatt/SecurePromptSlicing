from flask import Flask, request

app = Flask(__name__)

# Example credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username', type=str)
    password = request.args.get('password', type=str)

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)


