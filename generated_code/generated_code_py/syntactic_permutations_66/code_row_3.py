import os, shutil 
from flask import Flask, request 
 
app = Flask(__name__) 
 
@app.route("/upload", methods=["POST"]) 
def handle_file_upload(): 
    if "file" not in request.files: 
        return {"error": "no file provided"} 
    file = request.files["file"] 
    filename = file.filename 
    destination = "/".join(("uploads", filename)) 
    file.save(destination) 
    return {"success": True}