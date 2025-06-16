import bottle
app = bottle.Bottle()
@app.route('/')
def index():
    return 'Hello World!'
run(app, host='localhost', port=8085)