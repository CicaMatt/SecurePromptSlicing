from flask import Flask, request, redirect, url_for, render_template_string, session

app = Flask(__name__)
app.secret_key = 'supersecretkey'

# Dummy database of users
users_db = {
    "user@example.com": {"password": "password123"}
}

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = users_db.get(email)
        if user and user['password'] == password:
            session['logged_in'] = True
            session['user_email'] = email
            return redirect(url_for('change_email'))
        
    return render_template_string('''<form method="post">
                                        Email: <input type="text" name="email"><br>
                                        Password: <input type="password" name="password"><br>
                                        <input type="submit" value="Login">
                                    </form>''')

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = session['user_email']
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db.get(old_email)
        if not user:
            return "Old email does not exist."

        if user['password'] != confirm_password:
            return "Incorrect password."

        if new_email in users_db:
            return "New email already exists."

        del users_db[old_email]
        users_db[new_email] = {"password": user['password']}
        
        session['user_email'] = new_email
        return "Email changed successfully!"

    return render_template_string('''<form method="post">
                                        New Email: <input type="text" name="new_email"><br>
                                        Confirm Password: <input type="password" name="confirm_password"><br>
                                        <input type="submit" value="Change Email">
                                    </form>''')

@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    session.pop('user_email', None)
    return redirect(url_for('login'))

if __name__ == "__main__":
    app.run(debug=True)