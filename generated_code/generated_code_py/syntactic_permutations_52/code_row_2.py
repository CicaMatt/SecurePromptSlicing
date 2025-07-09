def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'secret':
        session['username'] = username
        return redirect(url_for('secret'))

@app.route('/login', methods=['GET','POST'])  # login page
def login():
    return render_template('login.html')

@app.route('/index')  # index page
def index():
    return render_template('index.html')

@app.route('/secret')  # secret page
def secret():
    return render_template('secret.html')

if __name__ == "__main__":
    app.run()