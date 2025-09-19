from flask import Flask, request, redirect, url_for, flash, session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": generate_password_hash("password123"), "email": "user@example.com"}
}

def is_logged_in():
    return session.get('logged_in', False) and session.get('current_email')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password'], password):
            session['logged_in'] = True
            session['current_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash("Invalid credentials!")
    
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session.get('current_email')
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and check_password_hash(user['password'], confirm_password):
            if new_email not in users_db:
                users_db[new_email] = {'password': user['password']}
                del users_db[old_email]
                session['current_email'] = new_email
                flash("Email updated successfully!")
                return redirect(url_for('change_email'))
            else:
                flash("New email already exists.")
        else:
            flash("Invalid password or incorrect old email.")

    current_email = session.get('current_email')
    return f'''
        <form method="post">
            Old Email: {current_email}<br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>

        <a href="/logout">Logout</a><br>
    '''

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)