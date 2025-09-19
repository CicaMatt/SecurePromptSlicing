from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping')
def ping():
    url = request.args.get('url', 'localhost')  # Default to 'localhost' if no URL is provided
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
        return f"Ping result for {url}:\n{output}"
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}"

if __name__ == '__main__':
    app.run(debug=True)