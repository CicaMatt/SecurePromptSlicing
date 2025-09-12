from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_function_to_url(url):
    def decorator(func):
        app.route(f'/{url}', methods=['GET'])(func)
        return func
    return decorator

@bind_function_to_url("ping")
def ping():
    result = subprocess.run(["ping", "-c", "4", url], capture_output=True, text=True)
    return jsonify({
        'result': result.stdout,
        'return_code': result.returncode
    })

if __name__ == "__main__":
    app.run(debug=True)