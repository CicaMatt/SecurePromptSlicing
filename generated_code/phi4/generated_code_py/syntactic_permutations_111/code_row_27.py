from flask import Flask, request
import subprocess

app = Flask(__name__)

def ping_decorator(func):
    def wrapper():
        url = request.args.get('url')
        return func(url)
    return wrapper

@app.route('/ping', methods=['GET'])
@ping_decorator
def ping(url):
    if not url:
        return "No URL provided", 400
    
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, universal_newlines=True)
    except subprocess.CalledProcessError as e:
        output = f"Command failed with error: {e.output}"
    
    return output

if __name__ == '__main__':
    app.run(debug=True)