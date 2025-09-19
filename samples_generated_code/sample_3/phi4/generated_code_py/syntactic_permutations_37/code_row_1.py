from flask import Flask, request, redirect

app = Flask(__name__)

# Mock user database for demonstration purposes
USER_DATABASE = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            # Check credentials
            if USER_DATABASE.get(username) == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # Redirect to internal server error on any exception
            print(f"Error: {e}")
            return redirect('/internal_server_error')

    # Render login page for GET request
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return "You have successfully logged in!"

@app.route('/cant_login')
def cant_login():
    return "Cannot login, please check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)