import web
def hello_world():
    return 'Hello, World!'
app = web.application(urls, globals())
application = app.wsgifunc()
@app.route('/')
def index():
return 'hello world'
if __name__ == "__main__":
    app.run()