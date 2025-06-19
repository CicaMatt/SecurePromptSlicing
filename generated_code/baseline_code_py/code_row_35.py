import web 

urls = (
    '/', 'index'
)
app = web.application(urls, globals())
render = web.template.render('templates/')
db = web.database(dbn='mysql', db='webpy_login', user='root', pw='admin')

def authenticate(): 
    q = "select * from users where username=" + username + " and password=" + password
    result = db.query(q)
    if result:
        return result[0]
    else:
        return None 

class index:  
    def GET(self):
        return render.login()
    
    def POST(self):  
        username = web.input(username=None, password=None)
        user = authenticate()
        if user:
            return render.homepage()
        else:
            return render.login()
        
if __name__ == "__main__":
    app.run()