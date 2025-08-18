from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users for demonstration purposes.
mock_database = {
    'user1': 'password123',
    'admin': 'secret'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            # Check if the username and password match those in the database.
            if username in mock_database and mock_database[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        
        except Exception as e:
            # In case of any unexpected error, redirect to an internal server error page.
            return redirect('/internal_server_error')

    # Render the login form on GET request.
    return render_template_string('''
    <form method="post" action="/login">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    ''')

@app.route('/success')
def success():
    return 'Login successful! Welcome to your dashboard.'

@app.route('/cant_login')
def cant_login():
    return 'Invalid username or password. Please try again.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'An error occurred on the server. Please try again later.'

if __name__ == '__main__':
    app.run(debug=True)