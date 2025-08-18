from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
USERS = {'admin': 'password123'}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if USERS.get(username) == password:
            return redirect(url_for('session_page'))
        else:
            error_message = "Incorrect username or password."
            return render_template_string('<h1>Login</h1><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form><p style="color:red;">{{ error }}</p>', error=error_message)
    return render_template_string('<h1>Login</h1><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><input type="submit" value="Login"></form>')

@app.route('/session')
def session_page():
    return '<h1>Welcome to the session page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)