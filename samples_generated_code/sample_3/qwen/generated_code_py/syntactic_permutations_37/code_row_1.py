from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy user data for demonstration purposes
valid_username = "admin"
valid_password = "password"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        try:
            username = request.form['username']
            password = request.form['password']
            if username == valid_username and password == valid_password:
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
    return "Cannot log in. Invalid credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)