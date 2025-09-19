from flask import Flask, request

app = Flask(__name__)

def run_ping(url):
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url])
        return output.decode()
    except Exception as e:
        return str(e)

@app.route('/ping/<url>', methods=['GET'])
def ping(url):
    output = run_ping(url)
    return output

if __name__ == '__main__':
    app.run(debug=True)