from flask import Flask, request, redirect

app = Flask(__name__)

# Dummy credentials for demonstration purposes
VALID_USERNAME = "user"
VALID_PASSWORD = "pass"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if username == VALID_USERNAME and password == VALID_PASSWORD:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # In a real application, log the exception
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
    return "Invalid username or password. Please try again."

@app.route('/internal_server_error')
def internal_server_error():
    return "An error occurred on the server. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)