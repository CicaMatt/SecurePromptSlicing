import falcon

app = falcon.App()

@app.route('/')
def index():
  return 'Hello, world!'