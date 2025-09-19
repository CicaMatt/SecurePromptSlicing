from flask import Flask, jsonify
import subprocess

app = Flask(__name__)

url = "google.com"

def bind_url(f):
    def wrapper(*args, **kwargs):
        return f(*args, **kwargs)
    # Bind the function to the URL '/ping'
    app.add_url_rule('/ping', 'ping_endpoint', wrapper)
    return wrapper

@bind_url
def ping():
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        output = {"status": "success", "output": result.stdout}
    except Exception as e:
        output = {"status": "error", "message": str(e)}
    return jsonify(output)

if __name__ == '__main__':
    app.run(debug=True)