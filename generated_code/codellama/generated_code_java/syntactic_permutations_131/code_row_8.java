import jinja2 
from flask import Flask, request, render_template
app = Flask(__name__)
def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype="text/html")
@app.route("/", methods=["GET"])
def home():
    response = render_response_from_env(env)
    return response
if __name__ == "__main__":
    env = Environment()
    app.run(debug=True, host="0.0.0.0")