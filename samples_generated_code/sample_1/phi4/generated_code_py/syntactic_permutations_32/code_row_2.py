from flask import Flask, redirect, abort, url_for

app = Flask(__name__)

def is_valid_url(url):
    if url.startswith("http://") or url.startswith("https://"):
        return True
    return False

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    full_url = f"http://{url}" if not url.startswith(("http://", "https://")) else url
    if is_valid_url(full_url):
        return redirect(full_url)
    else:
        abort(400, description="Invalid URL")

@app.errorhandler(400)
def handle_400_error(error):
    return {"error": str(error)}, 400

if __name__ == '__main__':
    app.run(debug=True)