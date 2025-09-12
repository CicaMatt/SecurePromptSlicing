from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<path:url>', methods=['GET'])
def ping(url):
    import subprocess
    command = ['ping', '-c', '4', url]
    result = subprocess.run(command, stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)