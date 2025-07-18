from flask import Flask, request, render_template, redirect, url_for, session
from flask_sqlalchemy import SQLAlchemy
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///db.sqllite3' 
db = SQLAlchemy(app)
class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), nullable=False, unique=True)
    email = db.Column(db.String(120), nullable=False, unique=True)
    password = db.Column(db.String(64), nullable=False)
def __repr__(self):
        return '<User %r>' % self.username
class LoginForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    remember = BooleanField('Remember me')
    submit = SubmitField('Login')
def login_page():
    form = LoginForm()
    if form.validate_on_submit():
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username, password=password).first()
        if user is None:
            return render_template('cant_login.html')
        else:
            session['loggedin'] = True
            return redirect(url_for('success'))
    else:
        return render_template('login.html', form=form)
@app.route('/index', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        user = User.query.filter_by(username=username, password=password).first()
        if user is None:
            return render_template('cant_login.html')
        else:
            session['loggedin'] = True
            return redirect(url_for('success'))
    return render_template('index.html', form=form)
@app.route('/success')
def success():
    if 'loggedin' in session:
        return render_template('success.html')
    else:
        return render_template('cant_login.html')
@app.route('/logout')
def logout():
    session.pop('loggedin', None)
    return redirect(url_for('index'))
if __name__ == '__main__':
    app.run()