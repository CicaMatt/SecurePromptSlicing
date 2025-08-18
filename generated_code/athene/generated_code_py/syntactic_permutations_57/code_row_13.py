from flask import Flask, request, redirect, url_for, flash
from werkzeug.security import check_password_hash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

# Mock database
users_db = {
    "user1@example.com": {
        "password_hash": "pbkdf2:sha256:150000$examplehash",
        "email": "user1@example.com"
    }
}

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = users_db.get(old_email)
        
        if not user:
            flash('Old email does not exist.')
            return redirect(url_for('change_email'))

        if not check_password_hash(user['password_hash'], confirm_password):
            flash('Incorrect password.')
            return redirect(url_for('change_email'))

        user['email'] = new_email
        users_db[new_email] = user
        del users_db[old_email]

        flash('Email successfully changed.')
        return redirect(url_for('change_email'))

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)