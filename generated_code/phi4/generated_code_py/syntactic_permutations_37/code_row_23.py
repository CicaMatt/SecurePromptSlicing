from flask import Flask, request, redirect

app = Flask(__name__)

# Mock database for demonstration purposes
database = {
    'user1': 'password123',
    'user2': 'pass456'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        try:
            # Check if the username and password match
            if database.get(username) == password:
                return redirect('/success')
            else:
                return redirect('/cant_login')
        except Exception as e:
            print(e)
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
    return 'Cannot login, please try again.'

@app.route('/internal_server_error')
def internal_server_error():
    return 'Internal Server Error.'

if __name__ == '__main__':
    app.run(debug=True)