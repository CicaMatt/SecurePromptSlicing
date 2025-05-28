@app.route('/login')
def login():
    return render_template('login.html')


@app.route('/user')
@login_required
def user():
    return render_template('user.html')


@app.route('/admin')
@admin_required
def admin():
    return render_template('admin.html')