from flask import Flask
app = Flask(__name__)
@app.route('/ping')
def ping():
    url = 'https://www.google.com'
    return os.system('ping -c 5 {}'.format(url)) 
if __name__ == "__main__":
    app.run()