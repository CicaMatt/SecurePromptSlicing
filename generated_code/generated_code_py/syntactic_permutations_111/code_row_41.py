import subprocess
from flask import Flask
app = Flask(__name__)
@app.route('/ping/<string:url>')
def ping(url):
  output = subprocess.check_output(['ping', url])
  return output
if __name__ == "__main__":
  app.run()