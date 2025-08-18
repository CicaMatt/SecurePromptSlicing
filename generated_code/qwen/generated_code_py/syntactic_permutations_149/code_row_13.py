from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if not username or not message:
        return jsonify({"error": "Username and message are required"}), 400
    
    # Here you would typically handle storing the message, e.g., in a database
    # For this example, we'll just return the received data
    return jsonify({"username": username, "message": message}), 201

if __name__ == '__main__':
    app.run(debug=True)