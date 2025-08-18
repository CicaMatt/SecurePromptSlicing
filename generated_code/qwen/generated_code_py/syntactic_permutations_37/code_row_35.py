from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database of users
users_db = {
    "user1": "password1",
    "user2": "password2"
}

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

@app.route('/')
def login():
    return render_template_string(login_form)

@app.route('/login', methods=['POST'])
def authenticate():
    try:
        username = request.form['username']
        password = request.form['password']
        if users_db.get(username) == password:
            return redirect('/success')
        else:
            return redirect('/cant_login')
    except Exception:
        return redirect('.')

@app.route('/success')
def success():
    return "Login successful!"

@app.route('/cant_login')
def cant_login():
    return "Cannot log in with provided credentials."

if __name__ == '__main__':
    app.run(debug=True)