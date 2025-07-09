from flask import Flask, send_file
app = Flask(__name__)
@app.route('/')
def home():
    if file_exists('index.html'):
        return send_file('index.html')
    else:
        return 'No such file'
if __name__ == "__main__":
    app.run(debug=True)