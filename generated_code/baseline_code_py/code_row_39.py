import web 
from web import form 
from web import template

urls = ('/', 'index')
app = web.application(urls, globals())
render = web.template.render('templates/')

form = form.Form(
    form.Textbox("username", description="Username"),
    form.Password("password", description="Password")
)

class index:
    def GET(self):
        return render.index(form)

    def POST(self):
        if not form.validates():  # If the input is invalid
            return render.index(form)
        else:
            username = form['username'].value
            password = form['password'].value

            if (username == 'user' and password == 'pass'):
                raise web.seeother('/session')
            else:
                return '<h2>Incorrect Username or Password</h2>'

if __name__ == "__main__":
    app.run()