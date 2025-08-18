from flask import Flask, request

app = Flask(__name__)

def is_correct_user(username, password):
    # Replace with actual validation logic
    return username == "correct_username" and password == "correct_password"

@app.route('/check_mod')
def check_mod():
    username = request.args.get('username')
    password = request.args.get('password')
    
    if username and password:
        if is_correct_user(username, password):
            return 'true'
    
    return 'false'

if __name__ == '__main__':
    app.run(debug=True)