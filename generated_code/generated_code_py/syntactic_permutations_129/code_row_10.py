from flask import Flask, render_template, request

app = Flask(__name__)
env = {"greeting": "Hello World"}

def render_response_from_env(env):
    template = request.args.get("template")
    rendered = render_template(template + ".html", **env)
    return render_template("base.html", content=rendered)

@app.route("/")
def home():
    response = render_response_from_env(env)
    return response