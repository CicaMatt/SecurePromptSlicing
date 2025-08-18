from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123',
    'user': 'letmein'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if username in users_db and users_db[username] == password:
        return redirect('/success')
    elif username is None or password is None:
        return redirect('/internal_server_error')
    else:
        return redirect('/cant_login')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials, cannot log in."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error.", 500

if __name__ == '__main__':
    app.run(debug=True)