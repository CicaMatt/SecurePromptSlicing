from flask import Flask, render_template, request, redirect, url_for
from flask_wtf import Form
from wtforms import StringField, PasswordField, SubmitField, BooleanField, SelectField
from wtforms.validators import InputRequired, Email, Length
from wtforms.widgets.html5 import EmailInput
import pymongo
from bson.json_util import dumps
# from bson.objectid import ObjectId
# from flask_login import LoginManager, login_user, logout_user, current_user, login_required

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secret'

client = pymongo.MongoClient('mongodb://localhost:27017/')
db = client['login_page']
users = db['users']

class LoginForm(Form):
    old_email = StringField('Old Email', validators=[InputRequired(), Email()], widget=EmailInput())
    new_email = StringField('New Email', validators=[InputRequired(), Email()], widget=EmailInput())
    password = PasswordField('Password', validators=[InputRequired()])
    submit = SubmitField('Update')

@app.route('/', methods=['GET', 'POST'])
def home():
    form = LoginForm()
    if request.method == 'POST' and form.validate_on_submit():
        old_email = form.old_email.data
        new_email = form.new_email.data
        password = form.password.data
        user = users.find_one({'old_email': old_email})
        if user:
            if check_password_hash(user['password'], password):
                users.update_one({'_id': ObjectId(user['_id'])}, {'$set': {'new_email': new_email}})
                return redirect('/')
    return render_template('index.html', form=form)

if __name__ == '__main__':
    app.run(debug=True)