from flask import Flask, request

app = Flask(__name__)

def run_ping(func):
    def wrapper():
        url = request.args.get('url')
        import subprocess
        try:
            output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:
            output = e.output
        return func(output.decode())
    return wrapper

@app.route('/ping', methods=['GET'])
@run_ping
def ping(output):
    return output, 200

if __name__ == '__main__':
    app.run(debug=True)