from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy data for demonstration
valid_username = 'admin'
valid_password = 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == valid_username and password == valid_password:
            return redirect(url_for('session_page'))
        else:
            return render_template_string('<p>Incorrect username or password. Please try again.</p><form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><button type="submit">Login</button></form>')
    else:
        return render_template_string('<form method="post">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><button type="submit">Login</button></form>')

@app.route('/session')
def session_page():
    return 'Welcome to the session page!'

if __name__ == '__main__':
    app.run(debug=True)