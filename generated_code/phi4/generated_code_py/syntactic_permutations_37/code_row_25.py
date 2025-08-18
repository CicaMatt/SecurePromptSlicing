from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Simple mock database as a dictionary
DATABASE = {
    "user1": "password123",
    "admin": "securepass"
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        try:
            # Check if the user exists and password matches
            if DATABASE.get(username) == password:
                return redirect(url_for('success'))
            else:
                return redirect(url_for('login_error'))
        except Exception as e:
            print(e)
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
    return "Login Successful!"

@app.route('/login_error')
def login_error():
    return "Invalid username or password."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error"

if __name__ == '__main__':
    app.run(debug=True)