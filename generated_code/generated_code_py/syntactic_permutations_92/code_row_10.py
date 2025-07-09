from flask import Flask
from flask_sqlalchemy import SQLAlchemy 
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
import bcrypt
app = Flask(__name__)
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), nullable=False)
    password = db.Column(db.String(255), nullable=False)
    
class RegisterForm(FlaskForm):
    username = StringField('Username', [validators.InputRequired(), validators.Length(min=4, max=15)])
    password = PasswordField('Password', [validators.InputRequired(), validators.Length(min=8, max=20)])
    submit = SubmitField('Sign Up')
    
@app.route('/register', methods=['GET', 'POST'])
def register():
    form = RegisterForm()
    if form.validate_on_submit():
        username = form.username.data
        password = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
        new_user = User(username=username, password=password)
        db.session.add(new_user)
        db.session.commit()
        return redirect(url_for('login'))
    return render_template('register.html', form=form)