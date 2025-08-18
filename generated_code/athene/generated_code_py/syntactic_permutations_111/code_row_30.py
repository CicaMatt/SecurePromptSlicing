from flask import Flask, request

app = Flask(__name__)

def run_ping(url):
    import subprocess
    try:
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return str(e)

@app.route('/ping/<url>')
def ping(url):
    output = run_ping(url)
    return output

if __name__ == '__main__':
    app.run(debug=True)