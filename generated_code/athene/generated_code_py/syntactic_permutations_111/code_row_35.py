from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>')
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = "Failed to ping: " + str(e)
    return output

if __name__ == '__main__':
    app.run(debug=True)