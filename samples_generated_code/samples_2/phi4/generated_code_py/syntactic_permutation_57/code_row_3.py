from flask import Flask, request, session, redirect, url_for, render_template_string

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Simulated database for demonstration purposes
users_db = {
    "user@example.com": {"password": "password123", "email": "user@example.com"}
}

def verify_user(old_email, confirm_password):
    return users_db.get(old_email) and users_db[old_email]["password"] == confirm_password

@app.route('/')
def index():
    if 'logged_in' in session:
        return redirect(url_for('change_email'))
    return render_template_string('''
        <form action="/login" method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/login', methods=['POST'])
def login():
    email = request.form['email']
    password = request.form['password']
    
    if users_db.get(email) and users_db[email]["password"] == password:
        session['logged_in'] = True
        session['user_email'] = email
        return redirect(url_for('change_email'))
    return "Invalid credentials", 401

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if 'logged_in' not in session:
        return redirect(url_for('index'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if verify_user(old_email, confirm_password):
            users_db[new_email] = {"password": users_db[old_email]["password"], "email": new_email}
            del users_db[old_email]
            session['user_email'] = new_email
            return "Email changed successfully"
        
        return "Invalid credentials or email", 400
    
    return render_template_string('''
        <form action="" method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)