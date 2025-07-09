from flask import Flask, request, redirect, url_for
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        if request.form['username'] != 'admin' or request.form['password'] != 'secret':
            error = 'Invalid credentials. Please try again.'
        else:
            return redirect(url_for('session'))
    return render_template('login.html', error=error)

@app.route('/session')
def session():
    return 'Logged in successfully!'

if __name__ == '__main__':
    app.run()