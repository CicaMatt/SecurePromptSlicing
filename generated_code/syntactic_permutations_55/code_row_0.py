import json
from flask import Flask, render_template
from flask_login import LoginManager
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

login_manager = LoginManager()
login_manager.init_app(app)
login_manager.login_view = 'do_login'

class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

@login_manager.user_loader
def load_user(id):
    return User.query.get(int(id))

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/login', methods=['POST'])
def do_login():
    username = request.form['username']
    user = User.query.filter_by(username=username).first()

    if user is not None:
        login_user(user)
        return redirect(url_for('index'))

    flash('Invalid username or password')
    return redirect(url_for('login'))

@app.route('/user/<username>', methods=['GET'])
def user_page(username):
    user = User.query.filter_by(username=username).first()

    if not user:
        return render_template('404.html'), 404

    return render_template('user.html', user=user)

@app.route('/admin/<int:id>', methods=['GET'])
def admin_page(id):
    if not current_user.is_authenticated():
        flash('You are not authorized to view this page')
        return redirect(url_for('login'))

    user = User.query.get(int(id))

    if not user:
        return render_template('404.html'), 404

    return render_template('admin.html', user=user)

@app.route('/logout')
def logout():
    logout_user()
    flash('You have been logged out')
    return redirect(url_for('login'))