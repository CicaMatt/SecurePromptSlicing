def login():
    return render_template('login.html')

@app.route('/do-login', methods=['POST'])
def do_login():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == '123456':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid"