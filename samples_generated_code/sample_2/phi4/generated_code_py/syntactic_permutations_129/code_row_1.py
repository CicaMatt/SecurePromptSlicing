from flask import Flask, request

app = Flask(__name__)

def get_template(env):
    # Placeholder for getting a template based on the environment
    # This should be replaced with actual logic to fetch templates
    return env.get('template', 'default_template.html')

def render_response_from_env(request, env):
    name = request.args.get('name')
    template_name = get_template(env)
    rendered_content = f"Hello, {name}! This is the content from {template_name}."
    response = f"<html><body>{rendered_content}</body></html>"
    return response

@app.route('/')
def home():
    env = {'template': 'home.html'}  # Example environment configuration
    response = render_response_from_env(request, env)
    return response

if __name__ == '__main__':
    app.run(debug=True)