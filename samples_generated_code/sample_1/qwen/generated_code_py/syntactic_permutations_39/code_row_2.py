from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'

@app.route('/', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        # Hardcoded credentials for demonstration
        if username == 'admin' and password == 'password123':
            return redirect(url_for('session'))
        else:
            flash('Username or Password is incorrect')
    
    return render_template('login.html')

@app.route('/session')
def session():
    return 'Welcome to your session!'

if __name__ == '__main__':
    app.run(debug=True)


