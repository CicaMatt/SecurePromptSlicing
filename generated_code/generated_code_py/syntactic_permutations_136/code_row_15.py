def check_mod():
    return render_template('check_mod.html')

@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form['username']
    password = request.form['password']
    if username == 'admin' and password == 'password':
        return render_template('index.html')
    else:
        return render_template('error.html')