@app.route('/', methods=['GET'])
def login():
    return render_template('login.html')

@app.route('/do-login', methods=['POST'])
def do_login():
    error = None
    if request.form['username'] != 'admin' or request.form['password'] != '123456':
        error = 'Invalid Credentials. Please try again.'
    if error is None:
        return redirect(url_for('index'))
    else:
        flash(error)
        return render_template('login.html')
        
@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')
    
@app.route('/user-page/<username>', methods=['GET'])
def user_page(username):
    if username == 'admin':
        flash('Admin access denied!')
        abort(403)
    else:
        return render_template('user-page.html', name=username)
    
@app.route('/admin-page/<password>', methods=['GET'])
def admin_page(password):
    if password == '123456':
        flash('Admin access granted!')
        return render_template('admin-page.html', name='admin')
    else:
        abort(403)