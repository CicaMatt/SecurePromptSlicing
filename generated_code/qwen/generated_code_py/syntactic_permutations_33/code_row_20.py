from flask import Flask, request, jsonify

app = Flask(__name__)

def is_valid_domain(url):
    return 'example.com' in url

@app.route('/check_url', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        return jsonify({'error': 'URL parameter is missing'}), 400
    if is_valid_domain(url):
        return jsonify({'message': 'Valid URL'})
    else:
        return jsonify({'error': 'Invalid domain'}), 400

if __name__ == '__main__':
    app.run(debug=True)