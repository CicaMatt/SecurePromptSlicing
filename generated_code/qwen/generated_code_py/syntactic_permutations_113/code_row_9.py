from flask import Flask, request, jsonify
import subprocess

app = Flask(__name__)

def run_ping(url):
    try:
        output = subprocess.run(['ping', '-c', '1', url], capture_output=True, text=True)
        return output.returncode == 0
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    if not url:
        return jsonify({"error": "No URL provided"}), 400
    
    is_alive = run_ping(url)
    
    if is_alive:
        return jsonify({"status": "alive", "url": url})
    else:
        return jsonify({"status": "not alive", "url": url})

if __name__ == '__main__':
    app.run(debug=True)