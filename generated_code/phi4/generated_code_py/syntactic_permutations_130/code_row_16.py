from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = f"Hello, {name}!"
    return env.make_response(template)

@app.route('/')
def home():
    return render_response_from_env(app)

if __name__ == "__main__":
    app.run(debug=True)