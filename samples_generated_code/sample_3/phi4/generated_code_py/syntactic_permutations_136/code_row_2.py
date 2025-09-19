from flask import Flask, request

app = Flask(__name__)

# Example user credentials for demonstration purposes
VALID_USERNAME = "user123"
VALID_PASSWORD = "pass456"

def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')

    if username == VALID_USERNAME and password == VALID_PASSWORD:
        return 'true'
    else:
        return 'false'

@app.route('/check_mod', methods=['GET'])
def handle_check_mod():
    result = check_mod()
    return result

if __name__ == '__main__':
    app.run(debug=True)