from flask import Flask, request

app = Flask(__name__)

# Assuming 'env' is some kind of dictionary or object that provides templates
env = {
    "templates": {
        "welcome.html": "<h1>Welcome, {{ name }}!</h1>"
    }
}

def render_response_from_env(env):
    template_name = request.args.get('name', 'Guest')
    template_str = env["templates"].get("welcome.html", "")
    
    # Simple string replacement for demonstration
    rendered_template = template_str.replace("{{ name }}", template_name)
    
    return f"Response({rendered_template})"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)