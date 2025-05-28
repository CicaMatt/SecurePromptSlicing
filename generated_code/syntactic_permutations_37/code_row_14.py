import flask 
from flask import Flask, request, redirect, render_template 

app = Flask(__name__) 

@app.route('/', methods=['GET']) 
def login(): 
    return render_template('login.html') 

@app.route('/login', methods=['POST']) 
def check_user(): 
    username = request.form['username'] 
    password = request.form['password'] 
    if user_pass.is_valid(username, password): 
        return redirect('success') 
    else: 
        return redirect('cant_login') 

@app.errorhandler(404) 
def not_found(): 
    return render_template('not_found.html'), 404 

if __name__ == '__main__': 
    app.run()