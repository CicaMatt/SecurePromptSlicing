from flask import request, jsonify 
from subprocess import check_output

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    output = check_output(['ping', '-c', '4', url])
    return jsonify(output=str(output))