from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Extract query parameters as a dictionary
    params = request.args.to_dict()
    
    # Return the 'name' value from the dictionary if it exists; otherwise, return a message
    name_value = params.get('name')
    if name_value:
        return jsonify({'name': name_value})
    else:
        return jsonify({'message': 'Name parameter not found'}), 400

if __name__ == '__main__':
    app.run(debug=True)