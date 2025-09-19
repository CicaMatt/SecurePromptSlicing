from flask import Flask, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database for demonstration
users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

def is_logged_in():
    return 'email' in session and 'password' in session

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != session['email']:
            return "Old email does not match the logged-in user."
        
        if new_email in users_db:
            return "New email already exists."

        if users_db[old_email]['password'] != confirm_password:
            return "Incorrect password."

        # Update the user's email
        user_data = users_db.pop(old_email)
        user_data['email'] = new_email
        users_db[new_email] = user_data

        session['email'] = new_email
        return "Email successfully changed."
    
    return '''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']

        if email in users_db and users_db[email]['password'] == password:
            session['email'] = email
            session['password'] = password
            return redirect(url_for('change_email'))
        
        return "Invalid credentials."

    return '''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)