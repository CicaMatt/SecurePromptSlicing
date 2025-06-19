import bottle
app = bottle.Bottle()
@app.route('/')
def index():
    return "Hello World!"
bottle.run(app)