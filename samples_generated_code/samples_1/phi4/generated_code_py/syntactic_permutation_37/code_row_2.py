from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database for demonstration purposes
users_db = {
    'user1': 'password123',
    'admin': 'adminpass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if users_db.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('login_failed'))
        except Exception as e:
            # Log the exception for debugging purposes
            print(e)
            return redirect(url_for('internal_server_error'))

    # GET request: show login form (HTML is simplified for brevity)
    return '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

@app.route('/success')
def success():
    return 'Login Successful! Welcome.'

@app.route('/login_failed')
def login_failed():
    return 'Login Failed. Please check your username and password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)