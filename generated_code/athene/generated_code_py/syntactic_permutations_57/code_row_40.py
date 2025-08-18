from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated user database
users_db = {
    'john.doe@example.com': {
        'password': 'securepassword123',
        'username': 'john_doe'
    }
}

# Simulated login status
logged_in_user = None

@app.route('/login', methods=['GET', 'POST'])
def login():
    global logged_in_user
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if email in users_db and users_db[email]['password'] == password:
            logged_in_user = email
            return redirect(url_for('change_email'))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not logged_in_user:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if old_email != logged_in_user or users_db[logged_in_user]['password'] != confirm_password:
            return "Invalid old email or password"

        # Update the user's email
        user_data = users_db.pop(logged_in_user)
        user_data['username'] = new_email.split('@')[0]
        users_db[new_email] = user_data
        logged_in_user = new_email

        return "Email changed successfully"
    
    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)