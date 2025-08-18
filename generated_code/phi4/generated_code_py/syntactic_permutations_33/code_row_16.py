from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

@app.route('/check-url/<path:url>', methods=['GET'])
def redirect_invalid_url(url):
    if url.startswith('http://') or url.startswith('https://'):
        return redirect(url)
    else:
        return jsonify({'error': 'Invalid URL'}), 400

if __name__ == '__main__':
    app.run(debug=True)