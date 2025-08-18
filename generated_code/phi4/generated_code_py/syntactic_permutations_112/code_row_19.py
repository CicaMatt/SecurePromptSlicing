from flask import Flask, request
import subprocess

app = Flask(__name__)
url = "google.com"

def bind_url_to_function(url):
    def decorator(func):
        app.add_url_rule(f'/{url}', view_func=func)
        return func
    return decorator

@bind_url_to_function("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return result.stdout if result.returncode == 0 else result.stderr

if __name__ == "__main__":
    app.run(debug=True)