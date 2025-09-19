from flask import Flask, request

app = Flask(__name__)

def run_ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}"

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is missing", 400
    result = run_ping(url)
    return result

if __name__ == '__main__':
    app.run(debug=True)