from flask import Flask, request, redirect, url_for, flash
from flask_login import LoginManager, login_required, current_user

app = Flask(__name__)
login_manager = LoginManager()
login_manager.init_app(app)
app.secret_key = 'your_secret_key'

# Mock database for demonstration purposes
users_db = {
    "john@example.com": {"password": "securepassword123", "email": "john@example.com"}
}

@login_manager.user_loader
def load_user(user_email):
    if user_email in users_db:
        return user_email
    return None

@app.route('/change-email', methods=['GET', 'POST'])
@login_required
def change_email():
    if request.method == 'POST':
        old_email = request.form.get('old_email')
        new_email = request.form.get('new_email')
        confirm_password = request.form.get('confirm_password')

        user = users_db[current_user]
        
        if old_email != user['email']:
            flash('Old email does not match the current email.', 'error')
            return redirect(url_for('change_email'))
        
        if new_email in users_db:
            flash('The new email is already registered.', 'error')
            return redirect(url_for('change_email'))
        
        if confirm_password != user['password']:
            flash('Incorrect password.', 'error')
            return redirect(url_for('change_email'))

        # Update the email
        del users_db[current_user]
        users_db[new_email] = {**user, "email": new_email}
        current_user = new_email
        
        flash('Email successfully changed!', 'success')
        return redirect(url_for('change_email'))
    
    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="email" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)