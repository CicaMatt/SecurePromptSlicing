from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simulated user database
user_db = {
    'user1': 'password123',
    'admin': 'securepass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            # Check credentials
            if username in user_db and user_db[username] == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('cant_login'))
        
        except Exception as e:
            # Handle any unexpected errors
            print(f"Error: {e}")
            return redirect(url_for('internal_server_error'))

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
    return "Login successful! Welcome."

@app.route('/cant_login')
def cant_login():
    return "Cannot login. Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "An error occurred on the server."

if __name__ == '__main__':
    app.run(debug=True)