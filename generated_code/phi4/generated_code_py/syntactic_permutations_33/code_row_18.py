from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/check-url/<path:url>', methods=['GET'])
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(f"http://{url}")
    else:
        return "Error: URL does not contain the domain example.com", 400

if __name__ == '__main__':
    app.run(debug=True)