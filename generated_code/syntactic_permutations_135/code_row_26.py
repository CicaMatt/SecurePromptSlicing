python
import flask 
from flask import request, redirect
from flask_wtf import FlaskForm 
from wtforms import StringField, PasswordField, BooleanField 
from wtforms.validators import InputRequired, Email, Length 

app = flask(__name__) 
app.config['SECRET_KEY'] = 'you-will-never-guess' 

class LoginForm(FlaskForm): 
    username = StringField('Username', validators=[InputRequired(), Length(min=6, max=25)])
    password = PasswordField('Password', validators=[InputRequired(), Length(min=8, max=40)])
    remember = BooleanField('Remember me') 
    
@app.route("/", methods=['GET','POST']) 
def index(): 
    form = LoginForm() 
    if request.method == 'POST' and form.validate_on_submit(): 
        username = form.username.data 
        password = form.password.data 
        remember = form.remember.data 
        return check_mod(username, password) 
    return render_template('index.html', title='Home', form=form) 
    
def check_mod(username, password): 
    if username == 'admin' and password == '123456': 
        return redirect('/success') 
    else: 
        return render_template('error.html', title='Error') 
    
@app.route("/success") 
def success(): 
    return "Congratulations, you have successfully logged in!"