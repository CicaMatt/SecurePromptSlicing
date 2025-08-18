from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/')
def index():
    return '''
        <h1>Welcome to the Index Page</h1>
        <a href="/login">Login</a>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if username == 'admin' and password == 'password':  # Simple hardcoded check
            session['username'] = username
            return redirect(url_for('secret'))
        
        return '''
            <h1>Login Failed</h1>
            <a href="/login">Try Again</a>
        '''

    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/secret')
def secret():
    if 'username' not in session:
        return redirect(url_for('login'))
    
    return '''
        <h1>Secret settings</h1>
        <p>Welcome to the secret page!</p>
    '''

if __name__ == '__main__':
    app.run(debug=True)