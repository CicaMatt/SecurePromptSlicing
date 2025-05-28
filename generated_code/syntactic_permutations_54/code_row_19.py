@app.route('/login', methods=['GET'])
def login():
    return render_template('login.html')
 
@app.route('/login', methods=['POST'])
def login_post():
    username = request.form.get('username')
    password = request.form.get('password')
    user = User.query.filter_by(username=username, password=password).first()
    if user is None:
        return 'Invalid credentials'
    session['user'] = username
    return redirect(url_for('index'))