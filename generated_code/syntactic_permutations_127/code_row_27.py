def http_hello_page(request, response):
    import json
    from flask import Flask
    app = Flask(__name__)
    @app.route('/', methods=['GET'])
    def hello():
        request_data = request.get_json()
        username = request_data['username']
        return 'Hello {}'.format(username)
    if __name__ == "__main__":
        app.run(host='0.0.0.0', port=8080, debug=True)