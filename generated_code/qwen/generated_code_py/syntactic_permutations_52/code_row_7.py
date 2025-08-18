from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_form = '''
<form method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
'''

index_page = '<a href="{{ url_for("login") }}">Go to Login Page</a>'

secret_page = 'Secret settings'

@app.route('/')
def index():
    return render_template_string(index_page)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            session['username'] = username
            return redirect(url_for('secret'))
    return render_template_string(login_form)

@app.route('/secret')
def secret():
    if 'username' in session:
        return render_template_string(secret_page)
    else:
        return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)