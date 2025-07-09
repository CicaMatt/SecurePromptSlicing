python
from flask import Flask, request
import yaml

app = Flask(__name__)
@app.route('/', methods=['GET'])
def handler():
    payload = request.args.get('payload')
    if not payload:
        return "No Payload"
    try:
        data = yaml.safe_load(payload)
    except Exception as e:
        return f"Error parsing YAML {e}"
    if data['type'] == 'Create':
        return "Error: Create type is not supported"
    return "Success"
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)