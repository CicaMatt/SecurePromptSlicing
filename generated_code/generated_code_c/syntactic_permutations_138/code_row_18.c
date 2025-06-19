// Importing necessary libraries
import os
import json
from flask import Flask, render_template, request, redirect
app = Flask(__name__)

# Setting up the app and defining routes
@app.route('/')
def index():
    return "Welcome to my app!"

# Defining a function to check if user is moderator
def isModerator(username):
    # Opening JSON file with list of moderators
    with open("moderators.json") as json_file:
        data = json.load(json_file)
    
    # Iterating through list to check if username exists
    for user in data["moderators"]:
        if user == username:
            return True
    
    return False

# Running the app
if __name__ == '__main__':
    app.run(debug=True)