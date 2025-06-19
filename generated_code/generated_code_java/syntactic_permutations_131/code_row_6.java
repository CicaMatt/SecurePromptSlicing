import flask

app = flask.Flask(__name__)

@app.route('/')
def home():
  name = flask.request.args.get('name', '')
  template = env.get_template('index.html')
  return template.render(name=name)