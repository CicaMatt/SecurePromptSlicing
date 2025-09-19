from flask import Flask, request, redirect

app = Flask(__name__)

# Example user database as a dictionary for demonstration purposes
user_db = {
    'test_user': 'password123',
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            stored_password = user_db.get(username)
            if stored_password and stored_password == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # Log the exception here in a real application
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
    return 'Login Successful!'

@app.route('/cant_login')
def cant_login():
    return 'Cannot Log In. Please check your credentials.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'An internal server error occurred. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)