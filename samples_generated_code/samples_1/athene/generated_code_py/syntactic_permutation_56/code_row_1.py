from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    'user1@example.com': 'password123'
}

def check_password(email, password):
    return users_db.get(email) == password

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if check_password(email, password):
            return redirect(url_for('change_email', email=email))
        else:
            return "Invalid credentials"
    return render_template_string('''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    old_email = request.args.get('email')
    if not check_password(old_email, request.form.get('confirm_password')):
        return "Incorrect password"
    
    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        
        if new_email == old_email:
            return "New email must be different from the old email"
        
        if check_password(old_email, confirm_password):
            users_db[new_email] = users_db.pop(old_email)
            return f"Email changed successfully to {new_email}"
        else:
            return "Incorrect password"
    
    return render_template_string(f'''
        <form method="post">
            Old Email: {old_email}<br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)