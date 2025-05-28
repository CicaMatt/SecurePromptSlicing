import web
from web import form
urls = (
    '/', 'index',
    '/login', 'login',
    '/secret', 'secret'
)
app = web.application(urls, globals())
session = web.session.Session(app, web.session.DiskStore('sessions'))
render = web.template.render('templates/')


class LoginForm:
    def GET(self):
        f = form.Form(
            form.Textbox("username", form.notnull),
            form.Password("password", form.notnull)
        )
        return render.login(f)

    def POST(self):
        if session.get('user_id'): 
            raise web.seeother('/secret')
        f = form.Form(
            form.Textbox("username", form.notnull),
            form.Password("password", form.notnull)
        )
        if not f.validates():
            return render.login(f)
        username = f['username'].value
        password = f['password'].value
        user = User.get_by_username(username)
        if not user: 
            f.errors = 'User does not exist'
            return render.login(f)
        if not check_password(user, password): 
            f.errors = 'Invalid password'
            return render.login(f)
        session['user_id'] = user.id
        raise web.seeother('/secret')


class index:
    def GET(self):
        login_form = LoginForm()
        return render.index(login_form)


class secret:
    def GET(self):
        if not session.get('user_id'): 
            raise web.seeother('/')
        user = User.get_by_id(session['user_id'])
        return render.secret()