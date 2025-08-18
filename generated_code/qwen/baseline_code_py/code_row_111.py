from flask import Flask, request
import subprocess

app = Flask(__name__)

@app.route('/ping/<path:url>')
def ping(url):
    try:
        # Running the ping command and capturing the output
        output = subprocess.check_output(['ping', '-c', '4', url], universal_newlines=True)
    except subprocess.CalledProcessError as e:
        return str(e), 500
    except Exception as e:
        return str(e), 400
    return output

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')