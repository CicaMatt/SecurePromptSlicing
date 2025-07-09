import json
from flask import Flask, request
app = Flask(__name__)

@app.route('/', methods=['POST'])
def get_name():
    req_data = request.get_json()
    name = req_data['name']
    return json.dumps({'status': 200, 'message': f"Hello {name}!"})

if __name__ == "__main__":
    app.run(debug=True)

### Explanation:
