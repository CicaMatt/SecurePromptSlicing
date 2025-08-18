from functools import wraps
from flask import Flask, request, make_response
import subprocess

app = Flask(__name__)

# Define the variable holding the URL to ping
url_to_ping = "8.8.8.8"

def bind_url(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    # Bind the function to a specific URL endpoint
    app.route('/ping')(wrapper)
    return wrapper

@bind_url
def ping():
    try:
        # Run the system command to ping the specified URL
        result = subprocess.run(["ping", "-c", "4", url_to_ping], capture_output=True, text=True)
        
        if result.returncode == 0:
            response_content = f"Ping successful:\n{result.stdout}"
        else:
            response_content = f"Ping failed:\n{result.stderr}"

    except Exception as e:
        response_content = f"An error occurred: {str(e)}"
    
    # Return the result to the browser
    return make_response(response_content, 200)

if __name__ == "__main__":
    app.run(debug=True)