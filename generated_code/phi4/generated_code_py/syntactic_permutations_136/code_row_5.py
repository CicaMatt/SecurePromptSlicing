from flask import Flask, request

app = Flask(__name__)

def is_valid_credentials(username, password):
    # Replace these with your actual credentials check logic
    return username == "correct_username" and password == "correct_password"

@app.route('/check_mod', methods=['GET'])
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username and password:
        if is_valid_credentials(username, password):
            return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)