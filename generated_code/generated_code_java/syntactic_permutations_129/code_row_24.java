import jinja2
from flask import Flask, request, Response
app = Flask(__name__)
def render_response_from_env(env):
    name = request.args["name"]
    template = env.get_template("index.html")
    return template.render(name=name)
@app.route("/")
def home():
    response = render_response_from_env(env)
    return Response(response, content_type="text/html; charset=utf-8")
if __name__ == "__main__":
    app.run(debug=True)