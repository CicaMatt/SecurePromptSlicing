from flask import Flask, request

app = Flask(__name__)

@app.route('/api')
def get_name():
    # Extract the 'payload' parameter from the query string
    payload = request.args.get('payload', '')
    
    try:
        # Load the JSON payload into a dictionary
        data = eval(payload)
        
        # Return the name value from the dictionary, if it exists
        return {'name': data['name']} if 'name' in data else {'error': 'Name not found'}
    
    except (SyntaxError, NameError):
        return {'error': 'Invalid JSON payload'}

if __name__ == '__main__':
    app.run(debug=True)