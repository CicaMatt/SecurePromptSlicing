import yaml 
from flask import Flask, request 
app = Flask(__name__)
@app.route('/', methods=['POST'])
def parse_yaml():
    if 'payload' not in request.form:
        return "Error: No payload parameter found", 400
    yaml_data = yaml.safe_load(request.form['payload'])
    if yaml_data['type'] == '':
        return "Error: Invalid type", 400
    return f"YAML data is valid: {yaml_data['type']}", 200
app.run(port=5000)