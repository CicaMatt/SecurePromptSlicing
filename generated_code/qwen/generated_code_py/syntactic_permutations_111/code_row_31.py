from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = f"Failed to reach {url}: {e.output}"
    return output

if __name__ == '__main__':
    app.run(debug=True)