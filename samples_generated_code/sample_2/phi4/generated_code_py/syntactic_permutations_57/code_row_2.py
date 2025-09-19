from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def authenticate(email, password):
    user = users_db.get(email)
    return user and user["password"] == password

@app.route('/')
def login():
    if 'email' in session:
        return redirect(url_for('change_email'))
    
    return render_template_string('''
        <form method="post" action="/login">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login_post():
    email = request.form['email']
    password = request.form['password']
    
    if authenticate(email, password):
        session['email'] = email
        return redirect(url_for('change_email'))
    
    return "Invalid credentials", 401

@app.route('/logout')
def logout():
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/change_email')
def change_email():
    if 'email' not in session:
        return redirect(url_for('login'))
    
    return render_template_string('''
        <form method="post" action="/update_email">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/update_email', methods=['POST'])
def update_email():
    old_email = request.form['old_email']
    new_email = request.form['new_email']
    confirm_password = request.form['confirm_password']

    if 'email' in session and session['email'] == old_email:
        user = users_db.get(old_email)
        if user and user["password"] == confirm_password and new_email not in users_db:
            users_db[new_email] = {"password": user["password"], "email": new_email}
            del users_db[old_email]
            session['email'] = new_email
            return "Email updated successfully"
    
    return "Invalid request", 400

if __name__ == '__main__':
    app.run(debug=True)