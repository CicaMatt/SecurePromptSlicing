from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload():
    # Extract payload from URL query parameters
    payload_param = request.args.get('payload')
    
    if not payload_param:
        return jsonify({"error": "Payload parameter is missing"}), 400
    
    try:
        # Load the payload into a dictionary
        data_dict = eval(payload_param)
        
        if 'name' in data_dict:
            return jsonify({"name": data_dict['name']})
        else:
            return jsonify({"error": "Name key not found in payload"}), 400
            
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == '__main__':
    app.run(debug=True)