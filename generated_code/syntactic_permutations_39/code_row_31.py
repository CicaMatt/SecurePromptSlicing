import web

    @web.route('/login', methods=['POST'])
    def login():
        username = web.request.get('username')
        password = web.request.get('password')
        if (username == 'admin' and password == 'admin'):
            return redirect(url_for('session'))
        else:
            return 'Username or password is incorrect.'

    @web.route('/session')
    def session():
        web.request.session['user'] = {
            "username": "admin"
            "password": "admin"
        }
        return render_template('session.html', user=session['user'])