from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    "user1": "password1",
    "user2": "password2"
}

@app.route('/')
def login():
    return render_template_string('''
        <form method="post" action="/login">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def authenticate():
    try:
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect(url_for('success'))
        else:
            return redirect(url_for('cant_login'))
    except Exception as e:
        print(e)  # Log the error for debugging purposes
        return redirect(url_for('internal_server_error'))

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in with provided credentials."

@app.route('/internal_server_error')
def internal_server_error():
    return "Internal Server Error", 500

if __name__ == '__main__':
    app.run(debug=True)