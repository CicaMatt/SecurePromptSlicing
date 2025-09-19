from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app)

def render_response_from_env(env):
    template_name = request.args.get('name', 'default_template.html')
    rendered_template = env.jinja_env.get_template(template_name).render()
    return f"<!doctype html><html lang='en'><body>{rendered_template}</body></html>"

if __name__ == '__main__':
    app.run(debug=True)