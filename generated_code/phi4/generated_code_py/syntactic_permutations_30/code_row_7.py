from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    return "Home Page"

@app.route('/redirect')
def handle_redirect():
    target_query_param = request.args.get('target', '')
    regex_pattern = r'^[\w-]+(\.[\w-]+)+$'
    
    if re.match(regex_pattern, target_query_param):
        return redirect(target_query_param)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)