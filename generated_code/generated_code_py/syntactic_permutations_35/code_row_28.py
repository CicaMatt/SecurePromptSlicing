import flask
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import DataRequired
app = flask(__name__)
app.config['SECRET_KEY'] = 'secret'
class LoginForm(FlaskForm):
    username=StringField('Username', validators=[DataRequired()])
    password=PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Log In')
@app.route('/login', methods=['GET', 'POST'])
def login():
    form=LoginForm()
    if form.validate_on_submit():
        username=form.username.data
        password=form.password.data
        user = check_user(username, password)
        if user:
            flask.session['user'] = user.username
            return redirect(url_for('home'))
    return render_template('login.html', form=form)
@app.route('/home')
def home():
    if 'user' not in flask.session:
        return redirect(url_for('login'))
    user = flask.session['user']
    return render_template('home.html', user=user)
if __name__ == '__main__':
    app.run()