from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env("home", env)

def render_response_from_env(name, env):
    template = env.get_template(f"{name}.html")
    response = template.render()
    return response