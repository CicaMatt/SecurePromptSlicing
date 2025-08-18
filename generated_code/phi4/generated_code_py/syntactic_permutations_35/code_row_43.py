from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
users_db = {
    'user1': 'password123',
    'admin': 'secret'
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username in users_db and users_db[username] == password:
            return redirect(url_for('home'))
        else:
            return redirect(url_for('login'))

    # Render the login form
    login_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    '''
    return render_template_string(login_html)

@app.route('/')
def home():
    return 'Welcome to the Home Page!'

if __name__ == '__main__':
    app.run(debug=True)