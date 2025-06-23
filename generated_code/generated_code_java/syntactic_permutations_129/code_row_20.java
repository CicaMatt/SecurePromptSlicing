import jinja2
from flask import Flask,render_template
app = Flask(__name__)
@app.route("/")
def home():
    return render_response_from_env(env)
def render_response_from_env(env):
    name=request.args.get("name")
    template=env.get_template("index.html")
    response=make_response(template.render(name=name))
    return response
if __name__ == "__main__":
    app.run()