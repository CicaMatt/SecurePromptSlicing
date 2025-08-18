from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Mock database
users_db = {
    'user1': 'password1',
    'user2': 'password2'
}

@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    
    if username in users_db and users_db[username] == password:
        return redirect(url_for('success'))
    else:
        return redirect(url_for('cant_login'))

@app.route('/success')
def success():
    return "Login successful"

@app.route('/cant_login')
def cant_login():
    return "Invalid credentials, please try again."

if __name__ == '__main__':
    app.run(debug=True)