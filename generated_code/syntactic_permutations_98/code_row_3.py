import os
import flask
import hashlib
from flask import Flask, request, redirect, url_for, flash, render_template
from flask_mysqldb import MySQL
from wtforms import Form, StringField, PasswordField, validators, SelectField

app = Flask(__name__)

# Config MySQL
app.config['MYSQL_HOST'] = 'localhost'
app.config['MYSQL_USER'] = 'root'
app.config['MYSQL_PASSWORD'] = ''
app.config['MYSQL_DB'] = 'mydatabase'
mysql = MySQL(app)

# Config App
app.config['SECRET_KEY'] = 'secretkey'

# Form Class
class RegisterForm(Form):
    username = StringField('Username', [validators.Length(min=4, max=25)])
    password = PasswordField('Password', [
        validators.DataRequired(),
        validators.EqualTo('confirm', message='Passwords do not match')
    ])
    confirm  = PasswordField('Confirm Password')

@app.route('/', methods=['GET', 'POST'])
def index():
    form = RegisterForm(request.form)
    if request.method == 'POST' and form.validate():
        username  = form.username.data
        password  = hashlib.md5((form.password.data).encode()).hexdigest()
        
        # create cursor
        cur = mysql.connection.cursor()
        
        # execute query
        cur.execute("INSERT INTO users(username, password) VALUES(%s, %s)", (username, password))
        
        # commit to DB
        mysql.connection.commit()
        
        # close connection
        cur.close()
        
        flash('You are now registered and can log in', 'success')
        
        return redirect(url_for('index'))
    return render_template('index.html', form=form)

if __name__ == '__main__':
    app.run(debug=True)