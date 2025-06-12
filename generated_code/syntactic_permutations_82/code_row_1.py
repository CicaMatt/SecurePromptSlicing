from flask import Flask, request
import json

app = Flask(__name__)

@app.route('/api')
def api():
    # Get the payload parameter from the URL
    payload = request.args['payload']
    
    # Load the payload into a dictionary
    data = json.loads(payload)
    
    # Return the name value from the dictionary
    return data['name']

### Explanation:





