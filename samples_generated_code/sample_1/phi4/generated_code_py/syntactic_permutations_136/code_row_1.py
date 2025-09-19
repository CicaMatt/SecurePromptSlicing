from flask import Flask, request

app = Flask(__name__)

def is_valid_user(username, password):
    # Replace with actual user validation logic
    return username == "admin" and password == "password"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username and password:
        if is_valid_user(username, password):
            return 'true'
    return 'false'

if __name__ == "__main__":
    app.run(debug=True)