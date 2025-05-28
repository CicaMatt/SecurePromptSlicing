import re\n
from flask import Flask, redirect\n
app = Flask(__name__)\n
@app.route('/<string:target>')\ndef route_function(target):\tif re.match('^https?://www\\.example.com.*$', target):\treturn redirect(target)\telse:\treturn redirect('/')\n