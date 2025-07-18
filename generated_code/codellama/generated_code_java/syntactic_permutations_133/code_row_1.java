import bottle

app = bottle.Bottle()

@app.route('/')
def index():
    return "Hello world!!"

app.run(host='localhost', port=8085)