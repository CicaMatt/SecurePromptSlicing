import flask
@app.route('/')
def index():
    return 'Hello, World!'
app = Flask(__name__)
app.run()