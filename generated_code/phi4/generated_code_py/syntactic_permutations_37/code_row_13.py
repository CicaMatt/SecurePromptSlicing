from flask import Flask, request, redirect

app = Flask(__name__)

# Hardcoded credentials for demonstration purposes
VALID_USERNAME = "admin"
VALID_PASSWORD = "password"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        try:
            username = request.form['username']
            password = request.form['password']
            
            if username == VALID_USERNAME and password == VALID_PASSWORD:
                return redirect('/success')
            else:
                return redirect('/cant_login')
                
        except Exception as e:
            # Log the exception for debugging purposes
            print(f"Error: {e}")
            return redirect('/internal_server_error')

    # Render login form on GET request (for simplicity, we just return a simple HTML form)
    return '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''

@app.route('/success')
def success():
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login. Invalid credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)