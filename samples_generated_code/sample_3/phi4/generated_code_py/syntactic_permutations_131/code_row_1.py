from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    user_request = request.form or request.args
    template_name = env.get('TEMPLATE_NAME')
    if not template_name:
        return "Template name not found in environment.", 400
    
    template_data = {key: value for key, value in user_request.items()}
    response = env['jinja_env'].get_template(template_name).render(**template_data)
    
    return f"Rendered Template:\n{response}", 200

@app.route('/')
def home():
    env = {
        'TEMPLATE_NAME': 'index.html',
        'jinja_env': app.jinja_env
    }
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)