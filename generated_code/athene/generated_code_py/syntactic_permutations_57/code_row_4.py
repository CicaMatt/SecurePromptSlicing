from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
users_db = {
    "user1@example.com": {"password": "securepass123"},
}

def is_logged_in():
    return 'user' in request.cookies

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if not is_logged_in():
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_data = users_db.get(old_email)
        if user_data and user_data['password'] == confirm_password:
            users_db[new_email] = users_db.pop(old_email)
            return "Email changed successfully."
        else:
            return "Invalid old email or password."

    return render_template_string('''
        <form method="post">
            Old Email: <input type="email" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    ''')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if email in users_db and users_db[email]['password'] == password:
            response = redirect(url_for('change_email'))
            response.set_cookie('user', email)
            return response
        else:
            return "Invalid credentials."
    return render_template_string('''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)