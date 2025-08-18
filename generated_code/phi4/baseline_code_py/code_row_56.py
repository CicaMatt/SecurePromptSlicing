from flask import Flask, request, render_template_string, session, redirect, url_for

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database
users_db = {
    'user1@example.com': {'password': 'password123', 'email': 'user1@example.com'}
}

def is_logged_in():
    return 'email' in session

@app.route('/')
def home():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    user_email = session['email']
    return f"Welcome {user_email}! <br><a href='/change-email'>Change Email</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('home'))
        
        return "Invalid credentials"

    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        if not user:
            return "User not found"
        
        if user['password'] != confirm_password:
            return "Password is incorrect"

        if old_email == new_email:
            return "New email must be different from the old email"

        # Update email
        del users_db[old_email]
        users_db[new_email] = {'password': user['password'], 'email': new_email}
        session['email'] = new_email

        return f"Email changed to {new_email}! <br><a href='/'>Go Home</a>"

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
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)