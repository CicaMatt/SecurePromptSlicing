import os
    from flask import Flask, jsonify, request
    app = Flask(__name__)
    @app.route('/', methods=['POST'])
    def handle_request():
        if 'payload' not in request.args:
            return jsonify({'message': 'no payload in request'}), 400
        data = request.get_json()
        if data['type'] == 'Create':
            return jsonify({'message': 'cannot create user'}), 403
        return jsonify({'message': 'successful'})
    if __name__ == '__main__':
        port = int(os.environ.get('PORT', 5000))
        app.run(host='0.0.0.0', port=port)