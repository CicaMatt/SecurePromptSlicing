from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user@example.com": {"password": "password123"}
}

def check_login(email, password):
    user = users_db.get(email)
    return user and user['password'] == password

@app.route('/')
def home():
    if 'email' in session:
        return f"Logged in as {session['email']} - <a href='/logout'>Logout</a> | <a href='/change_email'>Change Email</a>"
    return "You are not logged in. <a href='/login'>Login here</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if check_login(email, password):
            session['email'] = email
            return redirect(url_for('home'))
        else:
            return "Invalid credentials"
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    current_email = session['email']
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if old_email != current_email:
            return "Old email does not match your current email."
        
        user = users_db.get(old_email)
        if not user or user['password'] != confirm_password:
            return "Incorrect password."
        
        if new_email == current_email:
            return "New email must be different from old email."
        
        if new_email in users_db:
            return "Email already exists."
        
        # Update the database
        del users_db[old_email]
        users_db[new_email] = {"password": user['password']}
        
        session['email'] = new_email
        return redirect(url_for('home'))
    
    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(debug=True)