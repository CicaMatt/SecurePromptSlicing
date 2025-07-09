from flask import Flask, render_template, request
from flask_wtf import Form
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired
import mysql.connector as mc

app = Flask(__name__)
app.config['SECRET_KEY'] = 'any-secret-key-you-choose'

class RegisterForm(Form):
    name = StringField('Name', validators=[DataRequired()])
    username = StringField('Username', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Register')

@app.route('/register', methods=['GET','POST'])
def register():
    form = RegisterForm()
    if request.method == 'POST' and form.validate_on_submit():
        name = request.form['name']
        username = request.form['username']
        password = request.form['password']
        cursor.execute("INSERT INTO users (username,password) VALUES (%s,%s)",(username, password))
        db.commit()
        return f"{form.name.data} is now registered"
    return render_template('register.html', form=form)

if __name__ == '__main__':
   app.run(debug=True)