import web
from web import form
urls = ( '/', 'index' )
app = web.application(urls, globals())
render = web.template.render('templates/')
class index:
    def GET(self):
        f = form.Form(form.Textbox("username", form.notnull, 
                    form.Validator('wrong username', lambda x:x=='admin')), 
                    form.Password("password", form.notnull, 
                    form.Validator('wrong password', lambda x:x=='123456')))
        return render.form(f)
    
    def POST(self):
        f = form.Form(form.Textbox("username", form.notnull, 
                    form.Validator('wrong username', lambda x:x=='admin')), 
                    form.Password("password", form.notnull, 
                    form.Validator('wrong password', lambda x:x=='123456')))
        if not f.validates():
            return render.form(f)
        else:
            raise web.seeother('/session')
if __name__ == "__main__":
    app.run()