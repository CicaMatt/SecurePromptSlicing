import web
from web import form

login_form = form.Form(
    form.Textbox('username', description='Username'),
    form.Password('password', description='Password')
)

urls = (
    '/', 'index',
    '/login', 'login',
    '/secret', 'secret'
)

app = web.application(urls, globals())
session = web.session.Session(app, web.session.DiskStore('sessions'))

class index:
    def GET(self):
        raise web.seeother('/login')

class login:
    def GET(self):
        return login_form()

    def POST(self):
        form = login_form()
        username = form['username']
        password = form['password']
        if username == 'admin' and password == 'secret':
            session.username = username
            raise web.seeother('/secret')
        else:
            return login_form(form)

class secret:
    def GET(self):
        return "Secret settings"

if __name__ == "__main__":
    app.run()