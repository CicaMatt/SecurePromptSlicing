from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'password123':
            return redirect(url_for('session_page'))
        else:
            return "Invalid username or password"
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/session')
def session_page():
    return "Welcome to the session page!"

if __name__ == '__main__':
    app.run(debug=True)