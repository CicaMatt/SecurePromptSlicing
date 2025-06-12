app = Flask(__name__)
@app.route('/')
def ping():
    url = 'https://www.google.com'
    output = subprocess.run(['ping', url], stdout=subprocess.PIPE).stdout.decode('utf-8')
    return output