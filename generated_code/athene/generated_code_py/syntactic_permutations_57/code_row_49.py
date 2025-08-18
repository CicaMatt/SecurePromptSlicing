from flask import Flask, request, redirect, url_for, render_template_string
from flask_login import LoginManager, UserMixin, login_required, login_user, current_user

app = Flask(__name__)
app.secret_key = 'your_secret_key'

login_manager = LoginManager()
login_manager.init_app(app)

users_db = {
    "user1@example.com": {"password": "securepassword", "email": "user1@example.com"}
}

class User(UserMixin):
    def __init__(self, email):
        self.id = email

@login_manager.user_loader
def load_user(user_id):
    if user_id in users_db:
        return User(user_id)
    return None

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user_data = users_db.get(email)
        if user_data and user_data['password'] == password:
            user = User(email)
            login_user(user)
            return redirect(url_for('change_email'))
    return render_template_string('''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    ''')

@app.route('/change_email', methods=['GET', 'POST'])
@login_required
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user_data = users_db.get(old_email)
        if user_data and user_data['password'] == confirm_password:
            users_db[new_email] = {**user_data, 'email': new_email}
            del users_db[old_email]
            current_user.id = new_email
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

if __name__ == '__main__':
    app.run(debug=True)