import flask 
from flask import Flask, render_template, request, url_for, redirect, session, flash 
from flask_sqlalchemy import SQLAlchemy 
from datetime import datetime 
from functools import wraps 
from werkzeug.security import generate_password_hash, check_password_hash 
from sqlalchemy import create_engine 
import os 
app = Flask(__name__) 
# Database config 
basedir = os.path.abspath(os.path.dirname(__file__)) 
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///' + os.path.join(basedir, 'data.sqlite') 
app.config['SECRET_KEY'] = 'mysecretkey' 
db = SQLAlchemy(app) 
# Database models 
class User(db.Model): 
    __tablename__ = 'users' 
    id = db.Column(db.Integer, primary_key=True) 
    username = db.Column(db.String(64), unique=True, index=True) 
    email = db.Column(db.String(120), unique=True, index=True) 
    password_hash = db.Column(db.String(128)) 
    def __repr__(self): 
        return f"User('{self.username}', '{self.email}')" 
# User registration form 
class RegisterForm(FlaskForm): 
    username = StringField('Username', validators=[DataRequired(), Length(min=2, max=64)]) 
    email = StringField('Email', validators=[DataRequired(), Email()]) 
    password = PasswordField('Password', validators=[DataRequired()]) 
    confirm_password = PasswordField('Confirm Password', validators=[DataRequired(), EqualTo('password')]) 
    submit = SubmitField('Sign Up') 
# User login form 
class LoginForm(FlaskForm): 
    username = StringField('Username', validators=[DataRequired(), Length(min=2, max=64)]) 
    password = PasswordField('Password', validators=[DataRequired()]) 
    remember = BooleanField('Remember Me') 
    submit = SubmitField('Login') 
# User profile form 
class ProfileForm(FlaskForm): 
    username = StringField('Username', validators=[DataRequired(), Length(min=2, max=64)]) 
    email = StringField('Email', validators=[DataRequired(), Email()]) 
    submit = SubmitField('Update') 
# User change password form 
class ChangePasswordForm(FlaskForm): 
    old_password = PasswordField('Old Password', validators=[DataRequired()]) 
    new_password = PasswordField('New Password', validators=[DataRequired(), EqualTo('confirm_new_password')]) 
    confirm_new_password = PasswordField('Confirm New Password', validators=[DataRequired()]) 
    submit = SubmitField('Update Password') 
# User forgot password form 
class ForgotPasswordForm(FlaskForm): 
    email = StringField('Email', validators=[DataRequired(), Email()]) 
    submit = SubmitField('Send Reset Email') 
# User reset password form 
class ResetPasswordForm(FlaskForm): 
    new_password = PasswordField('New Password', validators=[DataRequired(), EqualTo('confirm_new_password')]) 
    confirm_new_password = PasswordField('Confirm New Password', validators=[DataRequired()]) 
    submit = SubmitField('Reset Password') 
# User change email form 
class ChangeEmailForm(FlaskForm): 
    new_email = StringField('New Email', validators=[DataRequired(), Email()]) 
    password = PasswordField('Password', validators=[DataRequired()]) 
    submit = SubmitField('Change Email') 
# User change username form 
class ChangeUsernameForm(FlaskForm): 
    new_username = StringField('New Username', validators=[DataRequired(), Length(min=2, max=64)]) 
    password = PasswordField('Password', validators=[DataRequired()]) 
    submit = SubmitField('Change Username') 
# Custom decorator to check if user is logged in or not. 
def login_required(f): 
    @wraps(f) 
    def wrap(*args, **kwargs): 
        if 'logged_in' in session: 
            return f(*args, *kwargs) 
        else: 
            flash("Unauthorized access, please login.", 'danger') 
            return redirect(url_for('login')) 
    return wrap 
# Custom decorator to check if user is admin or not. 
def admin_required(f): 
    @wraps(f) 
    def wrap(*args, **kwargs): 
        if 'logged_in' in session and session['username'] == current_app.config['ADMIN']: 
            return f(*args, *kwargs) 
        else: 
            flash("Unauthorized access, please login.", 'danger') 
            return redirect(url_for('login')) 
    return wrap 
# Custom decorator to check if user is account owner or not. 
def account_owner_required(f): 
    @wraps(f) 
    def wrap(*args, **kwargs): 
        if 'logged_in' in session and User.query.filter_by(username=session['username']).first(): 
            return f(*args, *kwargs) 
        else: 
            flash("Unauthorized access, please login.", 'danger') 
            return redirect(url_for('login')) 
    return wrap 
# Custom decorator to check if user is admin or account owner. 
def admin_or_account_owner_required(f): 
    @wraps(f) 
    def wrap(*args, **kwargs): 
        if 'logged_in' in session and User.query.filter_by(username=session['username']).first() or session['username'] == current_app.config['ADMIN']: 
            return f(*args, *kwargs) 
        else: 
            flash("Unauthorized access, please login.", 'danger') 
            return redirect(url_for('login')) 
    return wrap 
# Define routes 
@app.route('/') 
def index(): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return render_template('index-logged-in.html', username=session['username']) 
    else: 
        return render_template('index.html') 
@app.route('/login', methods=['GET', 'POST']) 
def login(): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return redirect(url_for('index')) 
    form = LoginForm() 
    if form.validate_on_submit(): 
        user = User.query.filter_by(username=form.username.data).first() 
        # Check if user exists and verify password 
        if user and check_password_hash(user.password_hash, form.password.data): 
            session['logged_in'] = True 
            session['username'] = user.username 
            flash('You are logged in successfully!', 'success') 
            return redirect(url_for('index')) 
        else: 
            flash('Invalid credentials, please try again.', 'danger') 
    return render_template('login.html', form=form) 
@app.route('/register', methods=['GET', 'POST']) 
def register(): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return redirect(url_for('index')) 
    form = RegisterForm() 
    if form.validate_on_submit(): 
        # Add new user to database 
        hashed_password = generate_password_hash(form.password.data, method='sha256') 
        new_user = User(username=form.username.data, email=form.email.data, password_hash=hashed_password) 
        db.session.add(new_user) 
        db.session.commit() 
        flash('You are registered successfully!', 'success') 
        return redirect(url_for('login')) 
    return render_template('register.html', form=form) 
@app.route('/logout') 
def logout(): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        session.clear() 
        flash('You are logged out successfully!', 'success') 
        return redirect(url_for('login')) 
    else: 
        flash("Unauthorized access, please login.", 'danger') 
        return redirect(url_for('login')) 
@app.route('/user/<username>') 
@login_required 
def user_page(username): 
    # Check if account owner or not 
    user = User.query.filter_by(username=username).first() 
    if 'logged_in' in session and session['username'] == username: 
        return render_template('user-account-owner.html', username=session['username']) 
    else: 
        return render_template('user.html', user=user) 
@app.route('/admin') 
def admin_page(): 
    # Check if admin or not 
    if 'logged_in' in session and session['username'] == current_app.config['ADMIN']: 
        return render_template('admin-dashboard.html', username=session['username']) 
    else: 
        flash("Unauthorized access, please login.", 'danger') 
        return redirect(url_for('login')) 
# Define error handlers 
@app.errorhandler(401) 
def page_not_found(e): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return render_template('page-not-found.html', username=session['username']), 401 
    else: 
        flash("Unauthorized access, please login.", 'danger') 
        return redirect(url_for('login')) 
@app.errorhandler(404) 
def page_not_found(e): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return render_template('page-not-found.html', username=session['username']), 401 
    else: 
        flash("Unauthorized access, please login.", 'danger') 
        return redirect(url_for('login')) 
@app.errorhandler(500) 
def page_not_found(e): 
    # Check if user is logged in or not 
    if 'logged_in' in session: 
        return render_template('page-not-found.html', username=session['username']), 401 
    else: 
        flash("Unauthorized access, please login.", 'danger') 
        return redirect(url_for('login')) 
if __name__ == "__main__": 
    app.run()