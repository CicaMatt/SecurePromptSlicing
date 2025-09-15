from flask import Flask, render_template, request, redirect, url_for, flash, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    'user1@example.com': {'password': 'password123'}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['email'] = email
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return render_template('login.html')

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('email', None)
    return redirect(url_for('login'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        user = users_db.get(old_email)
        
        if not user:
            flash('Old email does not exist')
        elif user['password'] != confirm_password:
            flash('Incorrect password')
        else:
            del users_db[old_email]
            users_db[new_email] = {'password': confirm_password}
            session['email'] = new_email
            flash('Email changed successfully')
    
    return render_template('change_email.html')

if __name__ == '__main__':
    app.run(debug=True)








