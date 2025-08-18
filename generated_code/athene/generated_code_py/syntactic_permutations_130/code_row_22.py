from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('home.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response

# Example usage with a mock environment
class MockEnvironment:
    def get_template(self, template_name):
        return lambda **kwargs: f"Hello, {kwargs['name']}! This is the {template_name}."

env = MockEnvironment()
app.add_url_rule('/', 'home', lambda: home(env))

if __name__ == '__main__':
    app.run(debug=True)