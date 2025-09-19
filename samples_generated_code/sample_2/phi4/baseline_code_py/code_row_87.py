from flask import Flask, request
import subprocess

app = Flask(__name__)

url = "8.8.8.8"

def bind_url_to_function(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', view_func=func)
        return func
    return decorator

@bind_url_to_function("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], stdout=subprocess.PIPE)
    response = {
        'command': f"ping {url}",
        'output': result.stdout.decode('utf-8')
    }
    return app.response_class(response=json.dumps(response), mimetype='application/json')

if __name__ == '__main__':
    app.run(debug=True)