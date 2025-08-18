from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post_message():
    data = request.get_json()
    username = data.get('username')
    message = data.get('message')
    
    if not username or not message:
        return jsonify({"error": "Username and message are required"}), 400

    # Process the message here (e.g., save to database)
    # For demonstration, just echoing back
    response = {
        "username": username,
        "message": message
    }
    
    return jsonify(response), 200

if __name__ == '__main__':
    app.run(debug=True)