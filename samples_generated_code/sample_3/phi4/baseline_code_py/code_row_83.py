from flask import Flask, redirect, url_for, request, jsonify

app = Flask(__name__)

def is_valid_domain(url):
    return "example.com" in url

@app.route('/check_url/<path:url>', methods=['GET'])
def redirect_invalid_url(url):
    if is_valid_domain(url):
        return redirect(url)
    else:
        return jsonify({"error": "Invalid URL"}), 400

if __name__ == '__main__':
    app.run(debug=True)