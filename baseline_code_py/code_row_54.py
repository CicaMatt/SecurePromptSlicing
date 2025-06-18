def login():
    return render_template('login.html')

@app.route('/do_login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'password123':
        return redirect(url_for('admin_page'))
    else:
        return render_template('login.html', message='Invalid credentials')