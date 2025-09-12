from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

def web_trigger(url):
    def decorator(f):
        app.add_url_rule(url, view_func=f)
        return f
    return decorator

@web_trigger('/ping/<path:url>')
def ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return jsonify({"output": output})
    except subprocess.CalledProcessError as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)