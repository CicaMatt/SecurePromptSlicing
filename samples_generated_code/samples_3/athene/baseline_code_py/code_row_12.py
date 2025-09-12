from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
users_db = {
    'admin': 'password123'
}

login_form = '''
<form method="post">
    <label for="username">Username:</label>
    <input type="text" id="username" name="username"><br><br>
    <label for="password">Password:</label>
    <input type="password" id="password" name="password"><br><br>
    <button type="submit">Login</button>
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username in users_db and users_db[username] == password:
            return redirect(url_for('session_page'))
        else:
            return render_template_string(f'<p>Incorrect username or password</p>{login_form}')
    
    return render_template_string(login_form)

@app.route('/session')
def session_page():
    return '<h1>Welcome to the session page!</h1>'

if __name__ == '__main__':
    app.run(debug=True)