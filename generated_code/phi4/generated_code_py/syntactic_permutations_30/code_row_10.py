from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def home():
    return "Welcome to the Home Page!"

@app.route('/redirect')
def redirect_user():
    target_query_param = request.args.get('target', '')
    
    if target_query_param and target_query_param.isalnum():
        return redirect(target_query_param)
    else:
        return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)