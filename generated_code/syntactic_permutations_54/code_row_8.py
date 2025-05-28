def login():
    form = '''<form method="POST">
    <label>Username:<input type='text' name='username'></label>
    <label>Password:<input type='password' name='password'></label>
    <input type="submit" value="Login">
    </form>'''
    return form
def do_login(environ):
    username = environ['wsgi.input'].read().decode().split('=')[1]
    password = environ['wsgi.input'].read().decode().split('=')[2][:-1]
    if username == 'admin' and password == 'password':
        return redirect(environ, '/admin_page')
    else:
        return
def redirect(environ, path):
    status = '303 See Other'
    headers = [('Location', path)]
    start_response(status, headers)
    return []