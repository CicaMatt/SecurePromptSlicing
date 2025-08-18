from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def url_trigger(route):
    def decorator(func):
        app.add_url_rule(route, view_func=func)
        return func
    return decorator

@url_trigger('/ping/<string:url>')
def ping(url):
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True, check=True)
        output = result.stdout
    except subprocess.CalledProcessError as e:
        output = f"An error occurred: {e}"
    return jsonify(output=output)

if __name__ == '__main__':
    app.run(debug=True)