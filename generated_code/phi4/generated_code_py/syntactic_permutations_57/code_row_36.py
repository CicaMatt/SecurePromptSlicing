from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    'user1@example.com': {'password': 'password123', 'email': 'user1@example.com'}
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/')
def index():
    if 'email' in session:
        return f'<h2>Welcome {session["email"]}! <a href="/change_email">Change Email</a> | <a href="/logout">Logout</a></h2>'
    else:
        return '<h2>Please <a href="/login">Login</a></h2>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if authenticate(email, password):
            session['email'] = email
            return redirect(url_for('index'))
        else:
            return '<h2>Invalid credentials</h2><a href="/login">Try again</a>'
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if user and user['password'] == confirm_password:
            if new_email in users_db:
                return '<h2>Email already exists</h2><a href="/change_email">Try again</a>'
            
            users_db[new_email] = {'password': user['password'], 'email': new_email}
            del users_db[old_email]
            session['email'] = new_email
            return redirect(url_for('index'))
        else:
            return '<h2>Incorrect password or email not found</h2><a href="/change_email">Try again</a>'
    
    return render_template_string('''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)