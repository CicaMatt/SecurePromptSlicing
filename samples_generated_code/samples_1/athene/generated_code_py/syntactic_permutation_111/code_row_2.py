from flask import Flask, request

app = Flask(__name__)

@app.route('/ping/<url>', methods=['GET'])
def ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '1', url], stderr=subprocess.STDOUT)
        return output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        return str(e.output.decode('utf-8')), 400

if __name__ == '__main__':
    app.run(debug=True)