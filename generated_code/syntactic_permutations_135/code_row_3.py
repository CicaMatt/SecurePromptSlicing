from flask import Flask, request, redirect
from flask_login import LoginManager, UserMixin, login_user, logout_user, current_user, login_required
import os
app = Flask(__name__)
app.secret_key = 'super secret string'  # Change this!

@app.route('/')
def index():
    return 'Hello World!'

class User(UserMixin):
    pass

@login_manager.user_loader
def user_loader(email):
    if email not in users:
        return
    user = User()
    user.id = email
    return user

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'GET':
        return '''
               <form action='login' method='POST'>
                <input type='text' name='username' id='username' placeholder='username'/>
                <input type='password' name='password' id='password' placeholder='password'/>
                <input type='submit' name='submit'/>
               </form>
               '''
    username = request.form['username']
    password = request.form['password']
    if check_login(username, password):
        user = User()
        user.id = username
        login_user(user)
        return redirect('/protected')
    return 'Bad login'

@app.route('/protected')
def protected():
    @login_required
    def foo():
        pass
    if current_user.is_authenticated:
        return f'Logged in as {current_user.id}'
    return 'Not logged in'

if __name__ == '__main__':
    app.run(debug=True)