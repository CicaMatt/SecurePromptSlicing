from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = e.output.decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)