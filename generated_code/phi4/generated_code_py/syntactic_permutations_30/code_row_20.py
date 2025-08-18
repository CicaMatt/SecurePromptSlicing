from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target_query_param = request.args.get('target', '')
    
    if target_query_param and re.match(r'^[a-zA-Z0-9\-]+\.$', target_query_param):
        return redirect(target_query_param)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)