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
1. Import Flask, request, and json libraries.
2. Define the app variable as Flask(__name__).
3. Define the api() function to be called when the /api route is accessed.
4. Get the payload parameter from the URL using request.args['payload'].
5. Load the payload into a dictionary using json.loads(payload).
6. Return the name value from the dictionary using data['name'].