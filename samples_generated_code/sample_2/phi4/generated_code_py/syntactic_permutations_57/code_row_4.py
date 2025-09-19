from flask import Flask, request, redirect, url_for, render_template_string, session, flash
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    'user@example.com': {'password': generate_password_hash('password123'), 'email': 'user@example.com'}
}

login_page = '''
<form method="post">
    <h2>Login</h2>
    Email: <input type="text" name="email"><br>
    Password: <input type="password" name="password"><br>
    <button type="submit">Login</button>
</form>
'''

change_email_page = '''
{% if message %}
<p>{{ message }}</p>
{% endif %}
<form method="post">
    <h2>Change Email</h2>
    Old Email: <input type="text" name="old_email"><br>
    New Email: <input type="text" name="new_email"><br>
    Confirm Password: <input type="password" name="confirm_password"><br>
    <button type="submit">Submit</button>
</form>
'''

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
        
        user = users_db.get(email)
        if user and check_password_hash(user['password'], password):
            session['user_email'] = email
            flash('Logged in successfully!')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials!')
    
    return render_template_string(login_page)

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        if old_email != session['user_email']:
            flash('Old email must match the logged-in user.')
        elif not users_db.get(old_email):
            flash('Old email does not exist.')
        elif not confirm_password:
            flash('Confirm password is required.')
        else:
            current_user = users_db[old_email]
            if check_password_hash(current_user['password'], confirm_password):
                if new_email in users_db:
                    flash('New email already exists.')
                else:
                    users_db[new_email] = users_db.pop(old_email)
                    session['user_email'] = new_email
                    flash('Email changed successfully!')
            else:
                flash('Incorrect confirm password.')

    return render_template_string(change_email_page)

if __name__ == '__main__':
    app.run(debug=True)