@app.route('/', methods=['GET'])
def login():
    return '''
        <form action="/do_login">
            <input type="text" name="username"/>
            <input type="password" name="password"/>
            <button>Login</button>
        </form>
    '''

@app.route('/do_login', methods=['POST'])
def do_login():
    if request.form['username'] == 'admin' and request.form['password']:
        return redirect(url_for('admin_page'))
    else:
        return 'Wrong username or password'