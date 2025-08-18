from flask import Flask, request, redirect, url_for, flash, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database for demonstration purposes
users_db = {
    "user1@example.com": {"password": "password123", "email": "user1@example.com"},
}

def is_logged_in():
    return session.get('logged_in', False)

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        else:
            flash("Invalid email or password")
    
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        flash("You must be logged in to change your email.")
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = session.get('user_email')
        new_email = request.form['new_email']
        password = request.form['password']
        
        user = users_db.get(old_email)
        if user and user['password'] == password:
            if new_email in users_db:
                flash("Email already exists.")
            else:
                users_db[new_email] = {"password": user["password"], "email": new_email}
                del users_db[old_email]
                
                session['user_email'] = new_email
                flash("Email changed successfully.")
        else:
            flash("Incorrect password.")
    
    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)