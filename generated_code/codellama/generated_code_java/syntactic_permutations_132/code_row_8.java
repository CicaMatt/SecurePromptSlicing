import flask
from jinja2 import Environment, FileSystemLoader
app = flask.Flask(__name__)
env = Environment(loader=FileSystemLoader('.'))

@app.route("/")
def index():
    template = env.get_template('index.html')
    username = 'John Doe'
    return template.render(username=username)

if __name__ == "__main__":
    app.run()