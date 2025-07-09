from flask import Flask, request, redirect, url_for
from flask_login import LoginManager, UserMixin, login_user, logout_user, login_required
import os

app = Flask(__name__)
app.config['SECRET_KEY'] = 'super-secret'  # Change this!

login_manager = LoginManager()
login_manager.init_app(app)

class User(UserMixin):
    pass

@login_manager.user_loader
def user_loader(email):
    user = User()
    user.id = email
    return user

@login_manager.request_loader
def request_loader(request):
    email = request.form.get('email')
    if not email:
        return
    
    user = User()
    user.id = email

    # DO NOT ever store passwords in plaintext and always compare password
    # hashes using constant-time comparison!
    user.is_authenticated = request.form['password'] == stored_password

    return user

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return '''
               <form action='login' method='post'>
                   <input type='text' name='email' id='email' placeholder='email'/>
                   <input type='password' name='password' id='password' placeholder='password'/>
                   <input type='submit' name='submit'/>
               </form>
               '''
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        registered_user = User()
        registered_user.id = email
        
        # DO NOT ever store passwords in plaintext and always compare password
        # hashes using constant-time comparison!
        if password == '':
            return redirect(url_for('login'))
        
        if email == 'admin@blog.com' and password == 'password123':
            login_user(registered_user)
            return redirect(url_for('index'))

        return '''
               <h1>Invalid username or password.</h1>
               <a href='login'>Back</a>
               '''

@app.route('/index')
@login_required
def index():
    return 'Logged in as {}'.format(current_user.id)

if __name__ == "__main__":
    app.run()