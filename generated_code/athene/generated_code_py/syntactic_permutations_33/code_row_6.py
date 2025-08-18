from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)