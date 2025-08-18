from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api', methods=['GET'])
def get_payload():
    # Extract query parameters from the request URL
    query_params = request.args.to_dict()

    # Return the payload as a JSON response
    return jsonify(query_params)

if __name__ == '__main__':
    app.run(debug=True)