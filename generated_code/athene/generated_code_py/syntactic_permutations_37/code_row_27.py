from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database
users_db = {
    'admin': 'password123',
    'user': 'pass456'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if not username or not password:
        return redirect('/internal_server_error')

    if username in users_db and users_db[username] == password:
        return redirect('/success')
    else:
        return redirect('/failure')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/failure')
def failure():
    return "Login failed!"

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)