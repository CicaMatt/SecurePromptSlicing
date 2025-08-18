from flask import Flask, redirect, request, abort

app = Flask(__name__)

def redirect_if_valid(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL domain.")

@app.route('/check_url', methods=['GET'])
def check_url():
    url = request.args.get('url')
    if not url:
        return "No URL provided.", 400
    return redirect_if_valid(url)

if __name__ == '__main__':
    app.run(debug=True)