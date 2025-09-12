from flask import Flask, request, session, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database of users
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

def validate_email(new_email):
    # Basic email validation
    if '@' in new_email and '.' in new_email.split('@')[-1]:
        return True
    return False

@app.route('/')
def home():
    if 'email' in session:
        return f'<h1>Welcome, {session["email"]}!</h1><br><a href="/change-email">Change Email</a>'
    return '<h1>Home Page</h1><br><a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if authenticate(email, password):
            session['email'] = email
            return redirect(url_for('home'))
        flash('Invalid credentials!')
    return render_template_string('''
        <h1>Login</h1>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
              {% for message in messages %}
                <li>{{ message }}</li>
              {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    current_email = session['email']
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        confirm_password = request.form.get('confirm_password')
        new_email = request.form.get('new_email')

        if authenticate(old_email, confirm_password):
            if validate_email(new_email) and new_email != current_email:
                users_db[new_email] = users_db.pop(current_email)
                session['email'] = new_email
                flash('Email changed successfully!')
                return redirect(url_for('home'))
            flash('Invalid new email or same as current email.')
        else:
            flash('Incorrect old email or password.')

    return render_template_string('''
        <h1>Change Email</h1>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
              {% for message in messages %}
                <li>{{ message }}</li>
              {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            New Email: <input type="text" name="new_email"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)