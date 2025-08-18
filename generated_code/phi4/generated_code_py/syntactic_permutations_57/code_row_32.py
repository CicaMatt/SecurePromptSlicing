from flask import Flask, request, redirect, url_for, session, flash, render_template_string

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def is_logged_in():
    return "email" in session

@app.route('/')
def index():
    if is_logged_in():
        email = session["email"]
        return f'Logged in as {email}. <a href="/change_email">Change Email</a> | <a href="/logout">Logout</a>'
    else:
        return 'You are not logged in. <a href="/login">Login</a>'

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        user = users_db.get(email)
        if user and user['password'] == password:
            session["email"] = email
            return redirect(url_for('index'))
        else:
            flash('Invalid email or password')
    
    login_form = """
    <form method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
    """
    return render_template_string(login_form)

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session["email"]
        new_email = request.form['new_email']
        password = request.form['password']

        user = users_db.get(old_email)
        if user and user['password'] == password:
            if new_email in users_db:
                flash('Email already exists.')
            else:
                # Change email
                del users_db[old_email]
                users_db[new_email] = {"password": password, "email": new_email}
                session["email"] = new_email
                flash('Email changed successfully!')
                return redirect(url_for('index'))
        else:
            flash('Invalid confirmation password.')

    change_email_form = """
    <form method="post">
        New Email: <input type="text" name="new_email"><br>
        Confirm Password: <input type="password" name="password"><br>
        <input type="submit" value="Change Email">
    </form>
    """
    return render_template_string(change_email_form)

@app.route('/logout')
def logout():
    session.pop("email", None)
    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)