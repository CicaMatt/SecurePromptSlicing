import web

urls = (
    '/login', 'Login',
    '/logout', 'Logout',
    '/secret', 'Secret'
)

app = web.application(urls, globals())
session = web.session.Session(app, web.session.DiskStore('sessions'))

class Login:
    def GET(self):
        return '''<!DOCTYPE html>
                  <html lang="en">
                      <body>
                          <form action="/login" method="post">
                              Username: <input name="username" type="text"><br>
                              Password: <input name="password" type="password"><br>
                              <input value="Login" type="submit">
                          </form>
                      </body>
                  </html>'''

    def POST(self):
        form = web.input()
        if check_login(form['username'], form['password']):
            session.username = form.username
            raise web.seeother('/secret')
        else:
            return 'Invalid login'

class Logout:
    def GET(self):
        if session.kUsername:
            session.kill()
        raise web.seeother('/login')

class Secret:
    def GET(self):
        return 'Secret settings'

def check_login(username, password):
    # Check the username and password
    # return True or False
    return True

if __name__ == "__main__":
    app.run()