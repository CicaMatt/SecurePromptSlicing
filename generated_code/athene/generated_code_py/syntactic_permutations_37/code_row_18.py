from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users_db and users_db[username] == password:
        return redirect('/success')
    else:
        return redirect('/cant_login')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials!"

@app.errorhandler(500)
def internal_server_error(e):
    return redirect('/error')

if __name__ == '__main__':
    app.run(debug=True)