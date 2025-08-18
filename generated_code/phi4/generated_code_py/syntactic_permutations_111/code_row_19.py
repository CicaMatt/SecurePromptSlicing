from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def url_trigger(route):
    def decorator(func):
        app.route(route)(func)
        return func
    return decorator

@url_trigger('/ping/<path:destination>')
def ping(destination):
    try:
        output = subprocess.check_output(['ping', '-c', '4', destination], universal_newlines=True)
        return jsonify({'output': output})
    except subprocess.CalledProcessError as e:
        return jsonify({'error': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)