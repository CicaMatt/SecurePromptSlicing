from flask import Flask, request

app = Flask(__name__)

def run_ping_command(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return f"Failed to ping {url}: {e}"

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    output = run_ping_command(url)
    return output

if __name__ == '__main__':
    app.run(debug=True)