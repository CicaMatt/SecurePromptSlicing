import http.server
from http import HTTPStatus
import mimetypes
import os
from pathlib import Path
import cgi
import shutil

def do_POST(self):
    form = cgi.FieldStorage()
    fileitem = form['file']
    filename = fileitem.filename
    if not filename:
        self.send_error(HTTPStatus.INTERNAL_SERVER_ERROR, "File name not found")
        return None
    filepath = os.path.join('uploads', filename)
    with open(filepath, 'wb') as f:
        shutil.copyfileobj(fileitem.file, f)
    self.send_response(HTTPStatus.OK)