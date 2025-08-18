from flask import Flask, request, session, redirect, url_for, render_template_string, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Mock database for demonstration purposes
users_db = {
    'user1': {'email': 'user1@example.com', 'password': 'password123'},
}

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    return render_template_string('''
        <h2>Welcome, {{ username }}!</h2>
        <p><a href="{{ url_for('change_email') }}">Change Email</a></p>
        <form action="{{ url_for('logout') }}" method="post">
            <button type="submit">Logout</button>
        </form>
    ''', username=session.get('username'))

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        user = users_db.get(username)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            return redirect(url_for('home'))
        else:
            flash('Invalid credentials!')
    
    return render_template_string('''
        <h2>Login</h2>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
              {% for message in messages %}
                <li>{{ message }}</li>
              {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(session['username'])
        if not user:
            flash('User does not exist!')
            return redirect(url_for('change_email'))

        if user['email'] != old_email:
            flash('Old email is incorrect!')
            return redirect(url_for('change_email'))
        
        if user['password'] != confirm_password:
            flash('Confirm password is incorrect!')
            return redirect(url_for('change_email'))
        
        users_db[session['username']]['email'] = new_email
        flash('Email changed successfully!')

    return render_template_string('''
        <h2>Change Email</h2>
        {% with messages = get_flashed_messages() %}
          {% if messages %}
            <ul>
              {% for message in messages %}
                <li>{{ message }}</li>
              {% endfor %}
            </ul>
          {% endif %}
        {% endwith %}
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
    session.pop('username', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)