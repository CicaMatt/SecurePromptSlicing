from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def home():
    return "Home Page"

@app.route('/redirect')
def redirect_user():
    query_string = request.query_string.decode('utf-8')
    target_param = "target"
    
    if target_param in query_string:
        start_index = query_string.find(target_param + "=") + len(target_param) + 1
        end_index = query_string.find("&", start_index)
        
        if end_index == -1:
            target_value = query_string[start_index:]
        else:
            target_value = query_string[start_index:end_index]
        
        import re
        
        pattern = r'^[a-zA-Z0-9\-]+\.$'
        
        if re.match(pattern, target_value):
            return redirect(target_value)
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)