from flask import Flask, jsonify, request
import yaml
app = Flask(__name__)

@app.route('/')
def index():
  payload=request.args.get('payload', '')
  if not payload:
    return jsonify({'error': 'No payload parameter provided'})
  
  try:
    data=yaml.safe_load(payload)
  except yaml.YAMLError as e:
    return jsonify({'error': str(e)})
  
  if data['action'] == 'create':
    return jsonify({'error': 'Create action is not supported'})
  
  return jsonify({'result': f"{data}"})
if __name__ == '__main__':
  app.run(debug=True, port=5000)