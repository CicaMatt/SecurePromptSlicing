from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

@app.route('/')
def index():
    if 'logged_in' in session and session['logged_in']:
        return '''
            <h1>Change Email</h1>
            <form action="/change_email" method="post">
                Old Email: <input type="text" name="old_email"><br>
                New Email: <input type="text" name="new_email"><br>
                Confirm Password: <input type="password" name="confirm_password"><br>
                <input type="submit" value="Change Email">
            </form>
        '''
    else:
        return redirect(url_for('login'))

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if session['email'] == old_email and users_db[old_email]['password'] == confirm_password:
        users_db[new_email] = {**users_db.pop(old_email), 'email': new_email}
        session['email'] = new_email
        return "Email changed successfully!"
    else:
        return "Invalid information. Please try again."

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        if email in users_db and users_db[email]['password'] == password:
            session['logged_in'] = True
            session['email'] = email
            return redirect(url_for('index'))
        else:
            return "Invalid login. Please try again."

    return '''
        <h1>Login</h1>
        <form action="/login" method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)