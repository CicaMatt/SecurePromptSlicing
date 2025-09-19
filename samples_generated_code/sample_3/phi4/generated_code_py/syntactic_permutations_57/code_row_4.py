from flask import Flask, request, session, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simple in-memory storage for demonstration purposes.
users = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

def check_login(email, password):
    user = users.get(email)
    return user and user['password'] == password

def change_email(old_email, new_email, confirm_password):
    if old_email not in users:
        raise ValueError("Old email does not exist.")
    
    user = users[old_email]
    if user['password'] != confirm_password:
        raise ValueError("Incorrect password.")
    
    if new_email in users:
        raise ValueError("New email already exists.")

    users[new_email] = {"password": user['password'], "email": new_email}
    del users[old_email]

@app.route('/')
def index():
    return render_template_string('''
        <h1>Welcome to the Login Page</h1>
        {% if 'email' in session %}
            <p>You are logged in as {{ session['email'] }}. <a href="{{ url_for('change_email_page') }}">Change email</a></p>
            <form action="{{ url_for('logout') }}" method="post">
                <input type="submit" value="Logout">
            </form>
        {% else %}
            <form action="{{ url_for('login') }}" method="post">
                Email: <input type="text" name="email"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Login">
            </form>
        {% endif %}
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']

    if check_login(email, password):
        session['email'] = email
        flash('Logged in successfully!')
        return redirect(url_for('index'))
    
    flash('Invalid credentials. Please try again.')
    return redirect(url_for('index'))

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('email', None)
    flash('You have been logged out.')
    return redirect(url_for('index'))

@app.route('/change-email')
def change_email_page():
    if 'email' not in session:
        flash('Please login to change your email.')
        return redirect(url_for('index'))
    
    return render_template_string('''
        <h1>Change Email</h1>
        <form action="{{ url_for('change_email_submit') }}" method="post">
            Old Email: <input type="text" name="old_email" required><br>
            New Email: <input type="email" name="new_email" required><br>
            Confirm Password: <input type="password" name="confirm_password" required><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/change-email-submit', methods=['POST'])
def change_email_submit():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if 'email' in session and session['email'] == old_email:
        try:
            change_email(old_email, new_email, confirm_password)
            flash('Email changed successfully!')
            session['email'] = new_email
        except ValueError as e:
            flash(str(e))
    
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)