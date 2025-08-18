from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Example user database for demonstration purposes.
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        
        try:
            # Check if username exists and password matches.
            if users_db.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cannot_login'))
        except Exception as e:
            # Redirect to error page in case of an exception
            return redirect(url_for('internal_server_error'))

    # Render login form (basic HTML for demonstration)
    return '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/success')
def success():
    return "Logged in successfully!"

@app.route('/cannot_login')
def cannot_login():
    return "Cannot login! Check your username and password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal server error occurred.", 500

if __name__ == '__main__':
    app.run(debug=True)