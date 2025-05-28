import flask 
    from flask_login import LoginManager, login_user, login_required, logout_user,current_user
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, BooleanField
    from wtforms.validators import InputRequired, Email, DataRequired
    from flask_sqlalchemy import SQLAlchemy 
    from werkzeug.security import generate_password_hash,check_password_hash

    app = Flask(__name__)
    app.config['SECRET_KEY']='secret-key'

    
### Note:
This challenge is not graded. This is only for demonstration purposes.