from flask import Flask, redirect, url_for, request, jsonify

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return jsonify({"error": "Invalid URL"}), 400

@app.route('/check-url/<path:url>', methods=['GET'])
def check_url(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)