from flask import Flask, request, redirect, url_for, flash
from flask_login import LoginManager, UserMixin, login_required, current_user, login_user

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'
login_manager = LoginManager(app)

users = {
    "user1@example.com": {"password": "password1", "email": "user1@example.com"}
}

class User(UserMixin):
    def __init__(self, email):
        self.id = email

@login_manager.user_loader
def load_user(email):
    if email in users:
        return User(email)
    return None

@app.route('/change_email', methods=['GET', 'POST'])
@login_required
def change_email():
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user_data = users.get(current_user.id)
        if not user_data:
            flash("User does not exist.")
            return redirect(url_for('change_email'))

        if old_email != current_user.id or user_data['password'] != confirm_password:
            flash("Incorrect email or password.")
            return redirect(url_for('change_email'))

        user_data['email'] = new_email
        users[new_email] = user_data
        del users[old_email]

        current_user.id = new_email
        flash("Email changed successfully.")
        return redirect(url_for('change_email'))

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user_data = users.get(email)
        if user_data and user_data['password'] == password:
            user = User(email)
            login_user(user)
            return redirect(url_for('change_email'))
        else:
            flash("Invalid credentials.")
    
    return '''
        <form method="post">
            Email: <input type="email" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)