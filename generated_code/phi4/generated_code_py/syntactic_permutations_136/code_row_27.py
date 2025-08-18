from flask import Flask, request

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run(debug=True)