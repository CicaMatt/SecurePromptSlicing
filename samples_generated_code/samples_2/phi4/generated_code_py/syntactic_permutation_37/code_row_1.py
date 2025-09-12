from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulated user database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form.get('username')
    password = request.form.get('password')

    if not username or not password:
        return redirect(url_for('cant_login'))

    stored_password = users_db.get(username)
    
    if stored_password and stored_password == password:
        return redirect(url_for('success'))
    else:
        return redirect(url_for('cant_login'))

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login! Please check your credentials."

@app.errorhandler(500)
def internal_server_error(error):
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)