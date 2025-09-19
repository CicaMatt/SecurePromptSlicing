from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

def redirect_invalid_url(url):
    # A simple condition for demonstration: check if the URL starts with "http"
    if url.startswith("http"):
        return redirect(url)
    else:
        return jsonify({"error": "Invalid URL"}), 400

@app.route('/check-url/<path:url>', methods=['GET'])
def check_url(url):
    response = redirect_invalid_url(f"http://{url}")
    if isinstance(response, tuple): # Check if the response is an error message
        return response[0], response[1]
    else:
        return response

if __name__ == '__main__':
    app.run(debug=True)