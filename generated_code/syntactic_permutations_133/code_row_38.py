import bottle
bottle = bottle.Bottle()
@bottle.route('/')
def index():
    return "Hello World!"
bottle.run(debug=True, reloader=True)