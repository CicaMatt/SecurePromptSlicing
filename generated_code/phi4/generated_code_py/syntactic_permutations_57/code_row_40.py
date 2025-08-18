from flask import Flask, request, redirect, url_for, session, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Dummy database of users for demonstration purposes
users_db = {
    "user@example.com": {
        "password": "$2b$12$somethinghashed",
        "email": "user@example.com"
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and check_password_hash(user['password'], password):
            session['user_email'] = email
            return redirect(url_for('change_email'))
        
        flash("Invalid email or password")
    
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_email' not in session:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session.get('user_email')
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if not user or not check_password_hash(user['password'], confirm_password):
            flash("Password confirmation failed")
        elif new_email in users_db:
            flash("New email already exists")
        else:
            users_db[new_email] = {
                "password": user["password"],
                "email": new_email
            }
            del users_db[old_email]
            
            session['user_email'] = new_email
            flash("Email updated successfully")

    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)