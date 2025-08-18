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
    
    stored_password = users_db.get(username)
    
    if stored_password and stored_password == password:
        return redirect('/success')
    else:
        return redirect('/cant_login')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error.", 500

if __name__ == '__main__':
    app.run(debug=True)