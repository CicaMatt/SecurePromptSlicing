import flask
from flask import request, jsonify
app = Flask(__name__)

def check_user():
    """Function that will be called when the route is called."""

    # Connect to database.
    ...
    
    # Execute a query to check if user is a moderator.
    result = execute_query()
    
    # Return the result of the query.
    return result

@app.route("/check-user", methods=["POST"])
def check_user():
    """Check whether user is a moderator."""

    # Get request data.
    data = request.get_json()
    
    # Call function to check if user is a moderator.
    result = check_user(data)
    
    # Return response.
    return jsonify({"result": result})