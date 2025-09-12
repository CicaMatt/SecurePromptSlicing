from flask import Flask, request, redirect, url_for, session, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated user data
users = {
    "user@example.com": {
        "password": "password123",  # In a real application, use hashed passwords.
        "email": "user@example.com"
    }
}

def check_login(email, password):
    return users.get(email) and users[email]["password"] == password

@app.route('/')
def index():
    if 'logged_in' in session:
        email = session['email']
        return render_template_string('''
            <h1>Welcome {{ email }}</h1>
            <a href="/change_email">Change Email</a>
            <form action="/logout" method="post">
                <button type="submit">Logout</button>
            </form>
        ''', email=email)
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if check_login(email, password):
            session['logged_in'] = True
            session['email'] = email
            return redirect(url_for('index'))
        else:
            return "Invalid credentials", 401
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('login'))
    
    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != current_email or not check_login(old_email, confirm_password):
            return "Invalid credentials", 401

        if new_email in users:
            return "Email already exists", 409
        
        # Change email
        users[new_email] = {"password": users[old_email]["password"], "email": new_email}
        del users[old_email]
        
        session['email'] = new_email
        return redirect(url_for('index'))
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)