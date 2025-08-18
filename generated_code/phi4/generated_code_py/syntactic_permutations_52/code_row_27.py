from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

@app.route('/')
def index():
    return render_template_string('''
        <h1>Secret Settings</h1>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if do_login(username, password):
            session['username'] = username
            return redirect(url_for('index'))
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

def do_login(username, password):
    # Simple check for demonstration purposes
    return username == 'admin' and password == 'password'

if __name__ == '__main__':
    app.run(debug=True)