from flask import Flask, request

app = Flask(__name__)

def check_mod(username, password):
    if username == 'admin' and password == 'password123':
        return True
    else:
        return False

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if check_mod(username, password):
        return 'true'
    else:
        return 'false'

if __name__ == '__main__':
    app.run()