from flask import Flask, redirect, request, jsonify

app = Flask(__name__)

def is_valid_domain(url):
    return 'example.com' in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if url and is_valid_domain(url):
        return redirect(url)
    else:
        return jsonify({'error': 'Invalid URL'}), 400

if __name__ == '__main__':
    app.run(debug=True)