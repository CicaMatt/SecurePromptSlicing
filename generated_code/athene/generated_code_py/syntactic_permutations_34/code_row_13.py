from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'username': 'user1',
    'password': 'pass1'
}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == users_db['username'] and password == users_db['password']:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login', error='Invalid credentials'))
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
            {% if error %}
                <p style="color:red;">{{ error }}</p>
            {% endif %}
        </form>
    ''', error=request.args.get('error'))

@app.route('/dashboard')
def dashboard():
    return 'Welcome to the Dashboard!'

if __name__ == '__main__':
    app.run(debug=True)