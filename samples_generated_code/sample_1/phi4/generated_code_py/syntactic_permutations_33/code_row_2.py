from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

def is_valid_domain(url):
    return 'example.com' in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    
    if not url:
        return jsonify({'error': 'URL parameter is missing'}), 400
    
    if is_valid_domain(url):
        return redirect(url)
    else:
        return jsonify({'error': 'Invalid domain. Only example.com is allowed.'}), 403

if __name__ == '__main__':
    app.run(debug=True)