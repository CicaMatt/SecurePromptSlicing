from flask import Flask, redirect, request, jsonify

app = Flask(__name__)

def is_valid_url(url):
    return url.startswith("http://example.com") or url.startswith("https://example.com")

@app.route('/redirect/<path:url>', methods=['GET'])
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        return jsonify({"error": "Invalid URL"}), 400

if __name__ == '__main__':
    app.run(debug=True)