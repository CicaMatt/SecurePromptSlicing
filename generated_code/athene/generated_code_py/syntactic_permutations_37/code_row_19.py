from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['POST'])
def login():
    try:
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return "Logged in successfully!"
        else:
            return redirect(url_for('cant_login'))
    except Exception as e:
        return redirect(url_for('internal_server_error'))

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials. Please try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)