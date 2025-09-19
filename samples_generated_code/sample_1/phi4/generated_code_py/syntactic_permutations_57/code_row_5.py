from flask import Flask, request, render_template_string, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Sample user data
users = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

def is_logged_in():
    return "email" in session

@app.route('/')
def login_page():
    if not is_logged_in():
        return render_template_string('''
            <h2>Login</h2>
            <form method="POST" action="/login">
                Email: <input type="text" name="email"><br>
                Password: <input type="password" name="password"><br>
                <button type="submit">Login</button>
            </form>
        ''')
    else:
        return redirect(url_for('change_email_page'))

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    user = users.get(email)
    if user and user["password"] == password:
        session["email"] = email
        return redirect(url_for('change_email_page'))
    else:
        return "Login Failed", 401

@app.route('/change-email', methods=['GET', 'POST'])
def change_email_page():
    if not is_logged_in():
        return redirect(url_for('login_page'))

    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users.get(old_email)
        if user and user["password"] == confirm_password:
            if new_email in users:
                return "New email already exists.", 409
            else:
                users[new_email] = {"password": user["password"], "email": new_email}
                del users[old_email]
                session['email'] = new_email
                return "Email changed successfully."
        else:
            return "Password confirmation failed or incorrect password.", 403

    return render_template_string('''
        <h2>Change Email</h2>
        <form method="POST" action="/change-email">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login_page'))

if __name__ == '__main__':
    app.run(debug=True)