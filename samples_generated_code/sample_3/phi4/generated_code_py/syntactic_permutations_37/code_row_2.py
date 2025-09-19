from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Example user data for demonstration purposes.
DATABASE = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check if the username and password are in the database
        if username in DATABASE and DATABASE[username] == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('failure'))

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

@app.route('/failure')
def failure():
    return 'Invalid username or password.'

@app.errorhandler(500)
def internal_server_error(error):
    return redirect(url_for('internal_error'))

@app.route('/error')
def internal_error():
    return 'Internal Server Error'

if __name__ == '__main__':
    app.run(debug=True)