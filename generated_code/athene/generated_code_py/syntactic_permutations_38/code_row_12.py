from flask import Flask, request, redirect, url_for

app = Flask(__name__)

users = {"admin": "password123"}

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username in users and users[username] == password:
            return redirect(url_for('dashboard'))
        else:
            return redirect(url_for('login', error='Invalid credentials'))
    else:
        error = request.args.get('error')
        return f'''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            {f'<p style="color:red;">{error}</p>' if error else ''}
            <input type="submit" value="Login">
        </form>
        '''

@app.route('/dashboard')
def dashboard():
    return "Welcome to the Dashboard!"

if __name__ == '__main__':
    app.run(debug=True)