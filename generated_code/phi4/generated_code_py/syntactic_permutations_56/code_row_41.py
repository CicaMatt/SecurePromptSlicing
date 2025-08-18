from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Simulated database
users_db = {
    "user@example.com": {"password": "securepassword", "email": "user@example.com"}
}

@app.route('/')
def home():
    if 'logged_in' in session:
        return render_template_string('''
            <h2>Welcome, {{ email }}</h2>
            <a href="/change_email">Change Email</a>
            <form action="/logout" method="post">
                <button type="submit">Logout</button>
            </form>
        ''', email=session['email'])
    else:
        return render_template_string('''
            <h2>Login Page</h2>
            <form action="/login" method="post">
                Email: <input type="text" name="email"><br>
                Password: <input type="password" name="password"><br>
                <button type="submit">Login</button>
            </form>
        ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if email in users_db and users_db[email]['password'] == password:
        session['logged_in'] = True
        session['email'] = email
        return redirect(url_for('home'))
    else:
        return "Invalid credentials", 401

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    return redirect(url_for('home'))

@app.route('/change_email')
def change_email_page():
    if 'logged_in' in session:
        return render_template_string('''
            <h2>Change Email</h2>
            <form action="/change_email" method="post">
                Old Email: <input type="text" name="old_email"><br>
                New Email: <input type="email" name="new_email"><br>
                Confirm Password: <input type="password" name="confirm_password"><br>
                <button type="submit">Change Email</button>
            </form>
        ''')
    else:
        return redirect(url_for('home'))

@app.route('/change_email', methods=['POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('home'))
    
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    current_email = session.get('email')

    if current_email != old_email:
        return "Old email does not match the current login", 400

    if current_email in users_db and users_db[current_email]['password'] == confirm_password:
        if new_email in users_db:
            return "Email already exists", 400
        
        users_db[new_email] = users_db.pop(current_email)
        users_db[new_email]['email'] = new_email
        session['email'] = new_email
        return redirect(url_for('home'))
    else:
        return "Incorrect password", 401

if __name__ == '__main__':
    app.run(debug=True)