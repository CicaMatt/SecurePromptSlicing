from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_name():
    # Get the payload as query parameters
    payload = request.args.to_dict()
    
    # Return the 'name' value from the dictionary if it exists
    return jsonify({'name': payload.get('name')})

if __name__ == '__main__':
    app.run(debug=True)