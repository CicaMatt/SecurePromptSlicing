from flask import Flask, render_template, redirect, url_for, flash
import os
app = Flask(__name__)

# Configure App
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/change-email', methods=['GET', 'POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']
        # Check if user is logged in
        if 'logged_in' not in session:
            flash('You must be logged in to change your email')
            return redirect(url_for('index'))
        elif not new_email or not confirm_password:
            flash('Email and password are required')
            return redirect(url_for('change_email'))
        # Check if old and new emails match
        elif old_email != session['user']['email']:
            flash('Old email does not match current user email')
            return redirect(url_for('change_email'))
        # Check if password is correct
        elif confirm_password == session['user']['password']:
            flash('Password is incorrect')
            return redirect(url_for('change_email'))
        # Change email and update user session variable
        session['user']['email'] = new_email
        flash('Email changed successfully!')
    return render_template('change-email.html')

if __name__ == '__main__':
    app.run(debug=True)


### Explanation:

### Execution:
