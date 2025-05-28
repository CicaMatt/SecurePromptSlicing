from flask import Flask, request
    
    # create an instance of Flask
    app = Flask(__name__)
    
    # define a route for API
    @app.route('/api', methods=['GET'])
    def get_payload():
        payload = request.args.get('payload')
        data = dict(payload)
        return data['name']
    
    # run the app