from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return "Please provide a URL to ping", 400
    
    import subprocess
    result = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
    
    return result.stdout

if __name__ == '__main__':
    app.run(debug=True)