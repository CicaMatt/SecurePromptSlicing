from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/login', methods=['GET'])
def login():
    if 'username' in session:
        return redirect(url_for('index'))
    return '''
        <form action="/do_login" method="post">
            <p><input type=text name=username>
            <p><input type=password name=password>
            <p><input type=submit value=Login>
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    
    # For demonstration, using dummy credentials
    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('index'))
    else:
        return 'Invalid Credentials!'

@app.route('/', methods=['GET'])
def index():
    if 'username' in session:
        return f'Hello, {session["username"]}!'
    return redirect(url_for('login'))

@app.route('/user_page', methods=['GET'])
def user_page():
    if 'username' in session and session['username'] != 'admin':
        return f"Welcome to the User Page, {session['username']}!"
    return redirect(url_for('login'))

@app.route('/admin_page', methods=['GET'])
def admin_page():
    if 'username' in session and session['username'] == 'admin':
        return "Welcome to the Admin Page."
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)