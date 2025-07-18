from flask import Flask, request, render_template

app = Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env(env)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    return template.render(name=name)