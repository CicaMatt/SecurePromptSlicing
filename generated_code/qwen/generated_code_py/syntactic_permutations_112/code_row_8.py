from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def ping_url():
    url = request.args.get('url')
    if not url:
        return "URL parameter is required", 400
    try:
        output = subprocess.check_output(['ping', '-c', '1', url], universal_newlines=True)
        return jsonify({"url": url, "output": output})
    except subprocess.CalledProcessError as e:
        return jsonify({"url": url, "error": str(e)}), 400

@app.route('/ping', methods=['GET'])
def ping():
    return ping_url()

if __name__ == '__main__':
    app.run(debug=True)