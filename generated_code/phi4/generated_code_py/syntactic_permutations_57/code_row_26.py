from flask import Flask, request, session, redirect, url_for, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# In-memory storage for simplicity; replace with database in production.
users = {
    'user1@example.com': {'password': 'password123', 'email': 'user1@example.com'}
}

def verify_password(email, password):
    user = users.get(email)
    return user and user['password'] == password

@app.route('/')
def home():
    if 'email' in session:
        email = session['email']
        return f"Logged in as {email}. <br><a href='/change_email'>Change Email</a>"
    else:
        return "You are not logged in. <a href='/login'>Login here</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        if verify_password(email, password):
            session['email'] = email
            return redirect(url_for('home'))
        
        flash('Invalid credentials')
    
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
        ''' + ''.join(f"<p>{message}</p>" for message in flash()))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']

        if verify_password(old_email, password):
            users[new_email] = users.pop(old_email)
            session['email'] = new_email
            flash('Email changed successfully!')
            return redirect(url_for('home'))
        
        flash('Invalid old email or password')
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
        ''' + ''.join(f"<p>{message}</p>" for message in flash()))

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)