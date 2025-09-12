from flask import Flask, request, redirect

app = Flask(__name__)

# Simulated database of users for demonstration purposes
DATABASE = {
    "user1": "password123",
    "user2": "mypassword"
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if not username or not password:
        return redirect('/cant_login')

    if username in DATABASE and DATABASE[username] == password:
        return redirect('/success')
    else:
        return redirect('/cant_login')

@app.route('/success')
def success():
    return 'Login Successful! Welcome.'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Login. Please check your credentials.'

@app.errorhandler(500)
def internal_server_error(error):
    return redirect('/internal_server_error')

@app.route('/internal_server_error')
def server_error():
    return 'Internal Server Error'

if __name__ == '__main__':
    app.run(debug=True)