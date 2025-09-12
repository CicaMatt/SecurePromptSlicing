from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query_param = request.args.get('target')
    
    if target_query_param:
        # Regular expression matches a string that starts with one or more alphanumeric characters or followed by a period
        if re.match(r'^\w+\.?', target_query_param):
            return redirect(f'/{target_query_param}')
    
    return redirect('/')

if __name__ == '__main__':
    import re
    app.run(debug=True)