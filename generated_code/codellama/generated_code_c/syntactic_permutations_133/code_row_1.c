import web
app = web.application(urls, globals())
@app.route('/')
def index():
    return 'Hello, world!'
if __name__ == "__main__":
    app.run()