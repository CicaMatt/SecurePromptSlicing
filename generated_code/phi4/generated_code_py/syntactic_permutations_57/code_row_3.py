from flask import Flask, request, redirect, url_for, render_template_string, session, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    'user@example.com': {'password': 'password123', 'email': 'user@example.com'}
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/')
def login():
    if 'email' in session:
        return redirect(url_for('change_email'))
    
    email = request.args.get('email')
    if email and authenticate(email, request.args.get('password')):
        session['email'] = email
        flash('Logged in successfully!', 'success')
        return redirect(url_for('change_email'))

    return render_template_string('''
        <h1>Login</h1>
        {% with messages = get_flashed_messages(with_categories=true) %}
          {% if messages %}
            {% for category, message in messages %}
              <div class="alert alert-{{ category }}">{{ message }}</div>
            {% endfor %}
          {% endif %}
        {% endwith %}
        <form method="get" action="/">
            <input type="email" name="email" placeholder="Email" required><br>
            <input type="password" name="password" placeholder="Password" required><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        flash('Please login to change email.', 'warning')
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if not authenticate(old_email, confirm_password):
            flash('Incorrect password.', 'danger')
            return redirect(url_for('change_email'))

        if new_email in users_db:
            flash('Email already exists.', 'danger')
            return redirect(url_for('change_email'))
        
        # Update email
        user['email'] = new_email
        session['email'] = new_email
        users_db[new_email] = user
        del users_db[old_email]
        flash('Email changed successfully!', 'success')

    return render_template_string('''
        <h1>Change Email</h1>
        {% with messages = get_flashed_messages(with_categories=true) %}
          {% if messages %}
            {% for category, message in messages %}
              <div class="alert alert-{{ category }}">{{ message }}</div>
            {% endfor %}
          {% endif %}
        {% endwith %}
        <form method="post" action="/change_email">
            <input type="email" name="new_email" placeholder="New Email" required><br>
            <input type="password" name="confirm_password" placeholder="Confirm Password" required><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)