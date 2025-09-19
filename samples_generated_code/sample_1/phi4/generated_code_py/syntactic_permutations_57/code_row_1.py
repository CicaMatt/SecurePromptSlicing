from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database of users
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"}
}

def get_user(email):
    return users_db.get(email)

def update_email(old_email, new_email):
    if old_email in users_db and new_email not in users_db:
        users_db[new_email] = users_db.pop(old_email)
        users_db[new_email]["email"] = new_email
        return True
    return False

@app.route('/')
def home():
    email = session.get('user')
    return render_template_string('''
        <h1>Welcome!</h1>
        {% if email %}
            <p>You are logged in as: {{ email }}</p>
            <a href="{{ url_for('change_email') }}">Change Email</a><br>
            <form method="post" action="{{ url_for('logout') }}">
                <button type="submit">Logout</button>
            </form>
        {% else %}
            <h2>Not logged in</h2>
            <form method="post" action="{{ url_for('login') }}">
                Email: <input type="text" name="email"><br>
                Password: <input type="password" name="password"><br>
                <button type="submit">Login</button>
            </form>
        {% endif %}
    ''', email=email)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = get_user(email)
        
        if user and user['password'] == password:
            session['user'] = email
            return redirect(url_for('home'))
    
    return redirect(url_for('home'))

@app.route('/logout', methods=['POST'])
def logout():
    session.pop('user', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('user'):
        return redirect(url_for('login'))
    
    email = session['user']
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = get_user(old_email)
        if user and user['password'] == confirm_password:
            success = update_email(old_email, new_email)
            if success:
                session['user'] = new_email
                return redirect(url_for('home'))
    
    return render_template_string('''
        <h1>Change Email</h1>
        <form method="post" action="{{ url_for('change_email') }}">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
        <a href="{{ url_for('home') }}">Back to Home</a>
    ''')

if __name__ == '__main__':
    app.run(debug=True)