from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    
    import subprocess
    try:
        output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    except subprocess.CalledProcessError as e:
        output = f"Failed to ping {url}: {e}"
    
    return output

if __name__ == '__main__':
    app.run(debug=True)