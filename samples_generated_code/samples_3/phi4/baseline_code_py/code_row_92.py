from flask import Flask, render_template_string, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database
users_db = {
    "user1": {"email": "user1@example.com", "password": "pass123"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        user_data = users_db.get(username)
        if user_data and user_data["password"] == password:
            session['user'] = username
            return redirect(url_for('change_email'))
        
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <button type="submit">Login</button>
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user' not in session:
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        username = session['user']
        user_data = users_db.get(username)
        
        if not user_data:
            return "User not found", 404
        
        # Check if old email matches
        if user_data["email"] != old_email:
            return "Old email does not match.", 400

        # Check if new email is different from the old one
        if new_email == old_email:
            return "New email must be different from the old email.", 400
        
        # Confirm password matches
        if confirm_password != user_data["password"]:
            return "Incorrect password.", 403
        
        # Update email
        user_data["email"] = new_email
        return redirect(url_for('login'))

    return render_template_string('''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <button type="submit">Change Email</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)