from flask import Flask, request

app = Flask(__name__)

def get_url(f):
    def wrapper(*args, **kwargs):
        url = request.args.get('url')
        return f(url, *args, **kwargs)
    return wrapper

@app.route('/ping', methods=['GET'])
@get_url
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)