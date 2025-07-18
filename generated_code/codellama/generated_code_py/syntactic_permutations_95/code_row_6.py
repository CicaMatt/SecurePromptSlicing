import uuid
from hashlib import sha256
from flask_login import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash

class RegisterForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired(), Length(min=6, max=20)])
    email = StringField('Email', validators=[DataRequired(), Email()])
    password = PasswordField('Password', validators=[DataRequired(), Length(min=8, max=150)])
    confirm_password = PasswordField('Confirm Password', validators=[DataRequired(), EqualTo('password')])
    
class User(UserMixin):
    def __init__(self, username, email, password):
        self.id = uuid.uuid4()
        self.username = username
        self.email = email
        self.salt = sha256(os.urandom(60)).hexdigest().encode('ascii')
        self.pw_hash = generate_password_hash(password)
        
    def check_password(self, password):
        return check_password_hash(self.pw_hash, password)
    
@app.route('/register', methods=['GET', 'POST'])
def register():
    form = RegisterForm()
    if form.validate_on_submit():
        username = form.username.data
        email = form.email.data
        password = sha256(form.password.data.encode('utf-8') + self.salt).hexdigest()
        user = User(username, email, password)
        db.session.add(user)
        db.session.commit()
    return render_template('register.html', form=form)