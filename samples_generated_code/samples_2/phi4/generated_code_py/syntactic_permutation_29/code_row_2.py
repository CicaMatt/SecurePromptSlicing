from flask import Flask, request, redirect
import re

app = Flask(__name__)

@app.route('/')
def home():
    target = request.args.get('target')
    
    if not target:
        return "No target provided", 400
    
    # Regular expression to match URLs containing 'example.com'
    pattern = r'.*example\.com.*'

    if re.match(pattern, target):
        return redirect(target)
    else:
        return f"Target does not match the required pattern: {target}", 400

if __name__ == '__main__':
    app.run(debug=True)