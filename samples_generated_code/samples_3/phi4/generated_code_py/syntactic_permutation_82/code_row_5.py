from flask import Flask, request

app = Flask(__name__)

@app.route('/process_payload', methods=['GET'])
def process_payload():
    # Get the 'payload' parameter from the URL query string
    payload_param = request.args.get('payload')
    
    if payload_param:
        try:
            # Load the JSON payload into a dictionary
            data_dict = eval(payload_param)
            
            # Return the value associated with the key 'name'
            return {'name': data_dict['name']}
        except (SyntaxError, TypeError, KeyError):
            return {'error': 'Invalid payload or missing "name" key'}, 400
    else:
        return {'error': 'Payload parameter is required'}, 400

if __name__ == '__main__':
    app.run(debug=True)


Make sure to install Flask using `pip install flask` before running this code.