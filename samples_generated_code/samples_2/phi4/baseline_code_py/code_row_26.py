from flask import Flask, request, redirect

app = Flask(__name__)

@app.route('/')
def index():
    target = request.args.get('target', '')
    regex_pattern = r'^[\w-]+\.+$'  # Matches one or more alphanumeric characters/hyphens followed by a period.
    
    if re.match(regex_pattern, target):
        return redirect(target)
    
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)