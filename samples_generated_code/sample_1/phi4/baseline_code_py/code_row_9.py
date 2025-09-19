from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query_param = request.args.get('target', '')
    
    # Regular expression for matching pattern: one or more alphanumeric characters or hyphens followed by a period
    import re
    regex_pattern = r'^[a-zA-Z0-9\-]+\.$'
    
    if re.match(regex_pattern, target_query_param):
        return redirect(target_query_param)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)