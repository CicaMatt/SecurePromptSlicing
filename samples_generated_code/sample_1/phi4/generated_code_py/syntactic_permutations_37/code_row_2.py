from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulating a simple in-memory database
users_db = {
    "user1": "password123",
    "admin": "adminpass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        # Check if the user exists and password matches
        if username in users_db and users_db[username] == password:
            return redirect(url_for('success'))
        
        # If login fails, redirect to an error page
        return redirect(url_for('internal_server_error'))
    
    # Render a simple HTML form for GET requests
    return '''
    <form method="post">
      Username: <input type="text" name="username"><br>
      Password: <input type="password" name="password"><br>
      <input type="submit" value="Login">
    </form>
    '''

@app.route('/success')
def success():
    return 'Login Successful! Welcome!'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Error: Invalid credentials, please try again.'

if __name__ == '__main__':
    app.run(debug=True)