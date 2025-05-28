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
* `from flask import Flask, render_template, redirect, url_for, flash` - imports the required modules for this application
* `@app.route('/')` - the route function is used to map the home page of the web app
* `@app.route('/change-email', methods=['GET', 'POST'])` - the route function is used to map the change email page of the web app
* `if request.method == 'POST':` - checks if the form has been submitted
* `old_email = request.form['old_email']` - obtains the old email from the form data
* `new_email = request.form['new_email']` - obtains the new email from the form data
* `confirm_password = request.form['confirm_password']` - obtains the confirm password from the form data
* `if 'logged_in' not in session:` - checks if the user is logged in, and if they are not, redirects them to the home page
* `flash('You must be logged in to change your email')` - displays a message on the page indicating that the user must log in to change their email
* `return redirect(url_for('index'))` - redirects the user back to the home page
* `elif not new_email or not confirm_password:` - checks if both the new email and confirm password are provided, and if they are not, redirects them to the change email page
* `flash('Email and password are required')` - displays a message on the page indicating that both the new email and confirm password are required
* `return redirect(url_for('change_email'))` - redirects the user back to the change email page
* `elif old_email != session['user']['email']:` - checks if the old email matches the current user's email, and if it does not, redirects them to the change email page
* `flash('Old email does not match current user email')` - displays a message on the page indicating that the old email does not match the current user's email
* `return redirect(url_for('change_email'))` - redirects the user back to the change email page
* `elif confirm_password == session['user']['password']:` - checks if the confirm password matches the current user's password, and if it does not, redirects them to the change email page
* `flash('Password is incorrect')` - displays a message on the page indicating that the confirm password is incorrect
* `return redirect(url_for('change_email'))` - redirects the user back to the change email page
* `session['user']['email'] = new_email` - updates the current user's session variable with the new email
* `flash('Email changed successfully!')` - displays a message on the page indicating that the email has been changed successfully
* `return render_template('change-email.html')` - renders the change email template and returns it to the user

### Execution:
This code can be run using Python 3 by executing the following command in the terminal: 
`python app.py`. This will start a web server on `http://127.0.0.1:5000/`, which can be opened in any web browser to see the application in action.