from flask import Flask, request

app = Flask(__name__)

def ping_url(f):
    def wrapper():
        url = request.args.get('url')
        if url:
            import subprocess
            try:
                output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, timeout=10)
            except subprocess.CalledProcessError as e:
                output = str(e.output)
            f(output.decode())
    return wrapper

@app.route('/ping')
@ping_url
def ping():
    url = request.args.get('url')
    if not url:
        return "Please provide a URL to ping."
    
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT, timeout=10)
    except subprocess.CalledProcessError as e:
        output = str(e.output)
    return output.decode()

if __name__ == '__main__':
    app.run(debug=True)