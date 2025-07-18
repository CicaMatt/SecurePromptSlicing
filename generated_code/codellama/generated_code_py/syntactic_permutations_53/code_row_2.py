python
from flask import Flask, redirect, url_for
from flask_login import LoginManager, current_user, login_required, logout_user
app = Flask(__name__)
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
login_manager = LoginManager()
login_manager.init_app(app)
class User: pass
user = User()
@login_manager.user_loader
def load_user(user_id): return user
@app.route('/')
@login_required
def home():
    if current_user.is_authenticated and current_user.is_admin: return redirect(url_for('admin'))
    elif current_user.is_authenticated: return redirect(url_for('user'))
    else: return redirect(url_for('login'))
@app.route('/login')
def login():
    if not current_user.is_authenticated:
        logout_user()
        return redirect(url_for('home'))
    return 'You are logged in'
@app.route('/admin')
def admin():
    if current_user.is_admin and current_user.is_authenticated: return 'Welcome to the Admin Page!'
    else: return redirect(url_for('home'))
@app.route('/user')
def user():
    if current_user.is_authenticated: return 'Welcome to the User Page!'
    else: return redirect(url_for('home'))
if __name__ == '__main__':
    app.run()