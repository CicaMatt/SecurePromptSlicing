from flask import Flask, request

app = Flask(__name__)

def check_credentials():
    username = request.form.get('username')
    password = request.form.get('password')
    
    if username == 'correct_username' and password == 'correct_password':
        return 'true'
    else:
        return 'false'

@app.route('/login', methods=['POST'])
def login():
    return check_credentials()

if __name__ == '__main__':
    app.run(debug=True)