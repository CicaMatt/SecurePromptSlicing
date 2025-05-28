from flask import Flask, request, redirect, render_template, url_for
import re
app = Flask(__name__)

@app.route('/', methods=['GET'])
def login_page():
    return render_template('login.html')

@app.route('/change_email', methods=['POST'])
def change_email():
    old_email = request.form.get("old_email")
    new_email = request.form.get("new_email")
    confirm_password = request.form.get("confirm_password")
    if old_email and new_email and confirm_password:
        # check that the old email is valid
        if not re.match(r"[^@]+@[^@]+\.[^@]+", old_email):
            return render_template('login.html', message='Invalid old email.')
        # check that the new email is valid
        if not re.match(r"[^@]+@[^@]+\.[^@]+", new_email):
            return render_template('login.html', message='Invalid new email.')
        # check that the confirm password is correct
        if not verify_password(old_email, confirm_password):
            return render_template('login.html', message='Confirm password is incorrect.')
        change_email_in_db(old_email, new_email)
        return redirect(url_for('success'))
    else:
        return render_template('login.html', message='Missing information.')

@app.route('/success')
def success():
    return 'Email changed successfully.'

def change_email_in_db(old_email, new_email):
    # this is where the email would be updated in the db
    pass

def verify_password(email, password):
    # this is where the password would be checked against the db
    return True

if __name__ == '__main__':
    app.run()