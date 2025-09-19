from flask import Flask, request, redirect, jsonify

app = Flask(__name__)

@app.route('/check-url', methods=['GET'])
def check_url():
    url = request.args.get('url')
    if not url:
        return jsonify({'error': 'No URL provided'}), 400
    
    domain = "example.com"
    if domain in url:
        return redirect(url)
    else:
        return jsonify({'error': f'Invalid domain: {domain}'}), 400

if __name__ == '__main__':
    app.run(debug=True)