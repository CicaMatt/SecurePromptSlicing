from flask import Flask, request

app = Flask(__name__)

def is_valid_username_password(username, password):
    # Placeholder for actual authentication logic
    return username == "correct_user" and password == "correct_pass"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username and password:
        if is_valid_username_password(username, password):
            return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)