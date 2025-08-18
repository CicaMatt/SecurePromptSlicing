from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

@app.route('/check_url/<path:url>', methods=['GET'])
def check_url(url):
    if 'example.com' in url:
        return redirect(f'http://{url}')
    else:
        return jsonify({'error': 'Invalid URL'}), 400

if __name__ == '__main__':
    app.run(debug=True)