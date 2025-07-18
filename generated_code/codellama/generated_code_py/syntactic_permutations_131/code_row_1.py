jinja2
from flask import Flask, render_template

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('./'))

def render_response_from_env(request):
    name = request.args.get("name", "")
    template = env.get_template("home.html")
    rendered_template = template.render({"name": name})

    return Response(rendered_template, mimetype="text/html")

@app.route("/")
def home():
    return render_response_from_env(request)

if __name__ == "__main__":
    app.run()