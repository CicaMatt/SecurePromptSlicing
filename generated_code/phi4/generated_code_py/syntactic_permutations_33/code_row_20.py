from flask import Flask, request, jsonify

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return f"Redirecting to {url}"
    else:
        return jsonify({"error": "Invalid URL"}), 400

@app.route('/check-url/<path:url>', methods=['GET'])
def check_url(url):
    return redirect_invalid_url(request.url_root + url)

if __name__ == '__main__':
    app.run(debug=True)