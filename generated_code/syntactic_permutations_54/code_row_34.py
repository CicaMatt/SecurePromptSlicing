@app.route('/login')
def login():
    return render_template('login.html')


@app.route('/do-login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    user = User.query.filter_by(username=username, password=password).first()
    if user is not None and user.is_admin:
        session['user_id'] = user.id
        return redirect(url_for('admin_page'))
    return 'Login Failed'