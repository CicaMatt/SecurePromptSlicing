from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/redirect')
def redirect_route():
    target = request.args.get('target', '/')
    
    # Define a simple regular expression (e.g., allows only alphanumeric and some special characters)
    import re
    pattern = r'^[a-zA-Z0-9_.-]+$'
    
    if re.match(pattern, target):
        return redirect(target)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)