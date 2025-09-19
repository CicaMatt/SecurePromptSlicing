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

    if not username or not password:
        return redirect('/internal_server_error')

    if username in users_db and users_db[username] == password:
        return redirect('/success')
    else:
        return redirect('/error')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/error')
def error():
    return "Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)