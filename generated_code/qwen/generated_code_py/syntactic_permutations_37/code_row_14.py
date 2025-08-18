from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy database of users
users = {
    "admin": "password123",
    "user": "pass456"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            if username in users and users[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            return redirect('/internal_server_error')
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in. Check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)