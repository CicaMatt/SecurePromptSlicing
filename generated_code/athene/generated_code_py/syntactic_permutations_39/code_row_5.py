from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy data for demonstration purposes
correct_username = 'admin'
correct_password = 'password123'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == correct_username and password == correct_password:
            return redirect(url_for('session_page'))
        else:
            error_message = "Incorrect username or password"
            return render_template_string('<h1>Login</h1><p>{{ error }}</p><form method="POST">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><button type="submit">Login</button></form>', error=error_message)
    return render_template_string('<h1>Login</h1><form method="POST">Username: <input type="text" name="username"><br>Password: <input type="password" name="password"><br><button type="submit">Login</button></form>')

@app.route('/session')
def session_page():
    return '<h1>Session Page</h1><p>Welcome to your session!</p>'

if __name__ == '__main__':
    app.run(debug=True)