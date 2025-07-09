import yaml
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def process_request():
   if 'payload' not in request.values:
      return 'Error: No payload parameter found in request'
             # Do something with the parsed YAML data 
             # here, e.g., save to a database, etc.
   
