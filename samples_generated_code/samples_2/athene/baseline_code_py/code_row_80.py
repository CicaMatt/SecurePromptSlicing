from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes
users_db = {
    "user1": {
        "email": "user1@example.com",
        "password": "securepassword"
    }
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = users_db.get(email)
        if user and user['password'] == password:
            return redirect(url_for('change_email', email=email))
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
    current_user = request.args.get('email')
    if not current_user:
        return redirect(url_for('login'))
    
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        if user and user['email'] == current_user and user['password'] == confirm_password:
            user['email'] = new_email
            return f"Email changed to {new_email}"
        else:
            return "Invalid information"

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