from flask import Flask, request

app = Flask(__name__)

def check_mod():
    username = request.form.get('username')
    password = request.form.get('password')
    if username == 'correct_user' and password == 'correct_password':
        return {'username': username, 'password': password}
    else:
        return False

@app.route('/login', methods=['POST'])
def login():
    result = check_mod()
    return str(result)

if __name__ == '__main__':
    app.run(debug=True)