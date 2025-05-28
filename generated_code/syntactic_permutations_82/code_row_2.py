import os
    import json
    from flask import Flask, request, jsonify
    
    app = Flask(__name__)
    
    @app.route('/api', methods=['GET'])
    def api():
        payload = dict(request.args)
        return jsonify({'name': payload.get('name')})
    
    if __name__ == '__main__':
        app.run()