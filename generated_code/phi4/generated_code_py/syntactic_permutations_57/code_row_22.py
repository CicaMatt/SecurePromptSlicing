from flask import Flask, render_template_string, request, redirect, url_for, session, flash

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory storage for demonstration purposes
users = {
    "user1": {"password": "password123", "email": "user1@example.com"}
}

@app.route('/')
def home():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    return render_template_string('''
        <h2>Welcome {{ user }}!</h2>
        <form action="/change-email" method="post">
            New Email: <input type="email" name="new_email"><br><br>
            Confirm Password: <input type="password" name="confirm_password"><br><br>
            <input type="submit" value="Change Email">
        </form>
        <a href="/logout">Logout</a>
    ''', user=session['user'])

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        if users.get(username) and users[username]['password'] == password:
            session['logged_in'] = True
            session['user'] = username
            return redirect(url_for('home'))
        else:
            flash('Invalid credentials')
    
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
        <form action="/login" method="post">
            Username: <input type="text" name="username"><br><br>
            Password: <input type="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change-email', methods=['POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    current_user = session['user']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if users[current_user]['password'] == confirm_password:
        users[current_user]['email'] = new_email
        flash('Email successfully changed!')
    else:
        flash('Incorrect password')

    return redirect(url_for('home'))

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)