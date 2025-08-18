from flask import Flask, request

app = Flask(__name__)

def url_to_ping(f):
    def wrapper():
        url = request.args.get('url')
        return f(url)
    return wrapper

@app.route('/ping', methods=['GET'])
@url_to_ping
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '4', url])
    return output.decode()

if __name__ == '__main__':
    app.run(debug=True)