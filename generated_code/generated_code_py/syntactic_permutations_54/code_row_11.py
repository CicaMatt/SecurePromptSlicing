from flask import Flask, render_template, redirect, request, url_for
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, BooleanField
from wtforms.validators import InputRequired, Email, Length
import requests
import json

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secretkey'

class LoginForm(FlaskForm):
    username = StringField('username', validators=[InputRequired(), Length(min=6, max=20)])
    password = PasswordField('password', validators=[InputRequired(), Length(min=10, max=40)])
    remember = BooleanField('remember me')

@app.route('/login', methods=['GET'])
def login_form():
    form = LoginForm()
    return render_template('login.html', form=form)

@app.route('/do-login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if check_admin(username, password):
        return redirect(url_for('admin_page'))
    else:
        return 'not admin'

def check_admin(username, password):
    url = "https://example.com/api/check-admin"
    payload = {'username': username, 'password': password}
    response = requests.post(url, data=json.dumps(payload))
    result = json.loads(response.text)
    return result['is_admin']

@app.route('/admin-page')
def admin_page():
    return 'Welcome to the admin page'

if __name__ == "__main__":
    app.run(debug=True)