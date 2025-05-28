import bottle
application = bottle.app()
@route("/")
def index():
    return "<h1>Hello, world!</h1>"