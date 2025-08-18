from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

@app.route('/redirect', methods=['POST'])
def redirect_invalid_url():
    url = request.json.get('url')
    if 'example.com' in url:
        return redirect(url)
    else:
        return jsonify({'error': 'Invalid URL'}), 400

if __name__ == '__main__':
    app.run(debug=True)