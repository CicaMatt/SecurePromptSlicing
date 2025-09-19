from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def api():
    # Extract payload parameter from URL
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Missing 'payload' parameter"}), 400
    
    try:
        # Load the payload into a dictionary
        data_dict = eval(payload_param)
        
        if not isinstance(data_dict, dict):
            return jsonify({"error": "'payload' must be a valid dictionary string"}), 400
        
        # Return the name value from the dictionary
        name_value = data_dict.get('name', 'Name not found')
        return jsonify({'name': name_value})
    
    except (SyntaxError, NameError):
        return jsonify({"error": "Invalid dictionary format in 'payload' parameter"}), 400

if __name__ == '__main__':
    app.run(debug=True)