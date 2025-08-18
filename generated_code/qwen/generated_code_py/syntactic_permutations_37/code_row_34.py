from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/')
def login():
    return '''
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/login', methods=['POST'])
def authenticate():
    username = request.form.get('username')
    password = request.form.get('password')

    try:
        if users_db[username] == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))
    except KeyError:
        return redirect(url_for('error'))

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Username or Password is incorrect."

@app.route('/error')
def error():
    return "An error occurred."

if __name__ == '__main__':
    app.run(debug=True)