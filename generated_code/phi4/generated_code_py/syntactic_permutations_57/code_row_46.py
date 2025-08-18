from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123"}
}

def is_logged_in():
    return 'email' in session

@app.route('/')
def index():
    if is_logged_in():
        return render_template_string('''
            <h2>Welcome, {{ email }}</h2>
            <a href="{{ url_for('change_email') }}">Change Email</a> |
            <form action="{{ url_for('logout') }}" method="post">
                <button type="submit">Logout</button>
            </form>
        ''', email=session['email'])
    else:
        return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = users_db.get(email)
        if user and user['password'] == password:
            session['email'] = email
            return redirect(url_for('index'))
        
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
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['email']
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        if user and user['password'] == confirm_password:
            if new_email in users_db:
                return "New email already exists", 400
            
            del users_db[old_email]
            users_db[new_email] = {"password": user['password']}
            session['email'] = new_email
            return redirect(url_for('index'))

        return "Invalid password or email does not exist", 401

    return render_template_string('''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)