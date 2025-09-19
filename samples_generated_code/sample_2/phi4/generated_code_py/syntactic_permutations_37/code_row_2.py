from flask import Flask, request, redirect, url_for
from werkzeug.security import check_password_hash

app = Flask(__name__)

# Example database of users with hashed passwords (use a real database in production)
users_db = {
    'user1': 'pbkdf2:sha256:150000$example_salt$user1password',
    # Add other users as needed
}

def check_user_credentials(username, password):
    user_record = users_db.get(username)
    if user_record and check_password_hash(user_record, password):
        return True
    return False

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            if check_user_credentials(username, password):
                return redirect(url_for('success'))
            else:
                return redirect(url_for('failure'))
        except Exception as e:
            # Log the exception in a real application
            return redirect(url_for('internal_server_error'))

    return '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

@app.route('/success')
def success():
    return 'Login successful!'

@app.route('/failure')
def failure():
    return 'Invalid username or password.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal server error occurred.', 500

if __name__ == '__main__':
    app.run(debug=True)