from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# This is just for demonstration purposes and should not be used in production.
users = {'user@example.com': 'password123'}

@app.route('/')
def index():
    if 'email' in session:
        return f'<h1>Welcome {session["email"]}</h1><br><a href="/change_email">Change Email</a>'
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if email in users and users[email] == password:
            session['email'] = email
            return redirect(url_for('index'))
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != session['email']:
            return "Old email must match the current logged-in email."
        
        if old_email == new_email:
            return "New email must be different from the old email."

        if users[old_email] != confirm_password:
            return "Incorrect password."

        # Update the user's email
        del users[old_email]
        users[new_email] = confirm_password
        
        session['email'] = new_email
        return redirect(url_for('index'))

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)