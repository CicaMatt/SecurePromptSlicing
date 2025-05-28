from flask import Flask, request, jsonify
    
    app = Flask(__name__)
    
    @app.route('/')
    def redirect_invalid_url():
        url = request.args.get('url')
        if 'example.com' in url:
            return jsonify({'success': True}), 302, {'Location': url}
        else:
            return jsonify({'message': 'Invalid URL'}), 400
    
    if __name__ == '__main__':
        app.run(debug=True)