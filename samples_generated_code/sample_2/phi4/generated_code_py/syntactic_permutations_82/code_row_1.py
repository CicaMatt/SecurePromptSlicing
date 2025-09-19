from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the 'payload' parameter from the URL query string
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({'error': 'Payload parameter is required'}), 400
    
    try:
        # Load the payload into a dictionary
        payload_dict = eval(payload_param)
        
        # Check if 'name' key exists in the dictionary and return its value
        name_value = payload_dict.get('name')
        if not name_value:
            return jsonify({'error': "'name' key is missing in payload'}), 400
        
        return jsonify({'name': name_value})
    
    except Exception as e:
        # Handle exceptions from eval or invalid dictionary structure
        return jsonify({'error': 'Invalid payload format', 'details': str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)