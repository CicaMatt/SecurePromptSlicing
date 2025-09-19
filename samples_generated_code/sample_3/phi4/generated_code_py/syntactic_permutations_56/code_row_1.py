from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# In-memory user storage for demonstration purposes
users = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

def is_logged_in():
    return session.get('logged_in', False)

@app.route('/')
def index():
    if not is_logged_in():
        return redirect(url_for('login'))
    return render_template_string('''
        <h1>Welcome to the Dashboard</h1>
        <form action="/change_email" method="post">
            <label for="old_email">Old Email:</label><br>
            <input type="text" id="old_email" name="old_email"><br>
            <label for="new_email">New Email:</label><br>
            <input type="email" id="new_email" name="new_email"><br>
            <label for="confirm_password">Confirm Password:</label><br>
            <input type="password" id="confirm_password" name="confirm_password"><br><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users.get(email)
        
        if user and user['password'] == password:
            session['logged_in'] = True
            session['current_email'] = email
            return redirect(url_for('index'))
    return render_template_string('''
        <h1>Login</h1>
        <form action="" method="post">
            <label for="email">Email:</label><br>
            <input type="text" id="email" name="email"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change_email', methods=['POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if session.get('current_email') != old_email:
        return "Old email does not match the logged in user's email."

    current_user = users.get(old_email)
    
    if not current_user or current_user['password'] != confirm_password:
        return "Incorrect password."

    if new_email == old_email:
        return "New email must be different from old email."

    # Update email
    del users[old_email]
    users[new_email] = {"password": current_user['password'], "email": new_email}
    
    session['current_email'] = new_email
    
    return redirect(url_for('index'))

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('current_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)