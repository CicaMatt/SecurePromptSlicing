from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def run_ping(url):
    try:
        output = subprocess.check_output(['ping', '-c', '1', url])
        return output.decode('utf-8'), 0
    except subprocess.CalledProcessError as e:
        return e.output.decode('utf-8'), e.returncode

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return jsonify({"error": "URL parameter is required"}), 400
    
    pong, status = run_ping(url)
    
    if status == 0:
        return jsonify({"url": url, "status": "alive", "output": pong})
    else:
        return jsonify({"url": url, "status": "not alive", "output": pong})

if __name__ == '__main__':
    app.run(debug=True)