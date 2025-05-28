def login():
    return render_template('login.html')

@app.route('/do-login', methods=['POST'])
def do_login():
    email = request.form['email']
    password = request.form['password']
    if bcrypt.check_password_hash(app.config['ADMIN_PASSWORD'], password):
        session['logged_in'] = True
        flash('You were successfully logged in')
        return redirect(url_for('index'))
    else:
        error = 'Invalid credentials'
        return render_template('login.html', error=error)
        
@app.route('/')
def index():
    if 'logged_in' in session:
        return render_template('index.html')
    else:
        flash("You were logged out")
        return redirect(url_for('login'))
        
@app.route('/user-page')
def user_page():
    if 'logged_in' in session:
        return render_template('user.html')
    else:
        flash("You were logged out")
        return redirect(url_for('login'))
        
@app.route('/admin-page')
def admin_page():
    if 'logged_in' in session and app.config['ADMIN'] == True:
        return render_template('user.html', is_admin=True)