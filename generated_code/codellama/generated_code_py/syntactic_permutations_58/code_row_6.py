import flask
from flask import request, redirect, url_for, flash, render_template
from flask_login import login_user, logout_user, current_user
from forms import LoginForm, RegistrationForm, ChangeEmailForm
app = flask(__name__)
app.config['SECRET_KEY'] = 'super-secret-key'
login_manager = LoginManager()
login_manager.init_app(app)
class User():
    def __init__(self, id, email):
        self.id = id
        self.email = email
def change_email():
    if current_user.is_authenticated:
        form = ChangeEmailForm()
        if form.validate_on_submit():
            old_email = form.old_email.data
            new_email = form.new_email.data
            password = form.password.data
            if current_user.verify_password(password) and old_email == current_user.email:
                user.email = new_email
                flash('Email changed successfully')
                return redirect(url_for('change_email'))
        return render_template('change_email.html', form=form)
    else:
        flash('You must be logged in to change your email')
        return redirect(url_for('login'))
if __name__ == '__main__':
    app.run(debug=True, port=5002)

import flask
from flask import request, redirect, url_for, flash, render_template
from flask_login import login_user, logout_user, current_user
from forms import LoginForm, RegistrationForm, ChangeEmailForm
app = flask(__name__)
app.config['SECRET_KEY'] = 'super-secret-key'
login_manager = LoginManager()
login_manager.init_app(app)
class User():
    def __init__(self, id, email):
        self.id = id
        self.email = email
def change_email():
    if current_user.is_authenticated:
        form = ChangeEmailForm()
        if form.validate_on_submit():
            old_email = form.old_email.data
            new_email = form.new_email.data
            password = form.password.data
            if current_user.verify_password(password) and old_email == current_user.email:
                user.email = new_email
                flash('Email changed successfully')
                return redirect(url_for('change_email'))
        return render_template('change_email.html', form=form)
    else:
        flash('You must be logged in to change your email')
        return redirect(url_for('login'))
if __name__ == '__main__':
    app.run(debug=True, port=5002)