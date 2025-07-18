import web
 
web.application(web.template.render)
 
@web.expose
 
def index():
 
    return "Hello, World!"
 
app = web.application(web.template.render)
 
if __name__ == "__main__":
 
    app.run()