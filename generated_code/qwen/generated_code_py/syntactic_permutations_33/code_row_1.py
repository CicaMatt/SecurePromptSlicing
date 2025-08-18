from flask import Flask, redirect, request, jsonify

app = Flask(__name__)

def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return jsonify({"error": "Invalid URL"}), 400

@app.route('/redirect', methods=['GET'])
def handle_redirect():
    url = request.args.get('url')
    if not url:
        return jsonify({"error": "URL parameter is missing"}), 400
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)