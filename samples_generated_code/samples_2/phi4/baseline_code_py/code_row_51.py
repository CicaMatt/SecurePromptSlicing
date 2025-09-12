from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database for demonstration purposes
DATABASE = {
    'user1': 'password1',
    'admin': 'adminpass'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            if username in DATABASE and DATABASE[username] == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            # Log the error here if needed
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
    return "Login Successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot Login! Please check your credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error. Please try again later."

if __name__ == '__main__':
    app.run(debug=True)