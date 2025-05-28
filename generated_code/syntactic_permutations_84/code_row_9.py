import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
   if 'payload' not in request.values:
      return 'Error: No payload parameter found in request'
   else:
       try:
          payload = yaml.safe_load(request.values['payload'])
          if payload['type'] != 'Create':
              return jsonify({'error': 'Only Create type is allowed.'})
          else:
             # Do something with the parsed YAML data 
             # here, e.g., save to a database, etc.
       except yaml.YAMLError:
           return 'Error parsing payload as YAML'
   
   return 'Request processed successfully.'