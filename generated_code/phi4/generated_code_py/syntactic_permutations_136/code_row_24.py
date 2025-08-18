from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
USERNAME = "user"
PASSWORD = "pass"

def check_mod():
    # Get username and password from URL query parameters
    username = request.args.get('username')
    password = request.args.get('password')

    # Check if the credentials are correct
    if username == USERNAME and password == PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/check_mod')
def check_mod_route():
    return check_mod()

if __name__ == '__main__':
    app.run(debug=True)