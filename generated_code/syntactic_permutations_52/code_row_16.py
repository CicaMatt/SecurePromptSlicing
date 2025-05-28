from flask import Flask, render_template, request, redirect, session
app = Flask(__name__)
app.config['SECRET_KEY']='mysecretkey'
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method=='POST':
        username = request.form['username']
        password = request.form['password']
        if username=='admin' and password == 'password123':
            session['username'] = username
            return redirect('/secret')
        else:
            return '<h1>Invalid username or password</h1><a href="/login">Try again</a>'
    else:
        return render_template('login.html')

@app.route('/secret')
def secret():
    if 'username' in session:
        return '<h1>Secret settings</h1>'
    else:
        return redirect('/login')

if __name__=='__main__':
    app.run(debug=True)