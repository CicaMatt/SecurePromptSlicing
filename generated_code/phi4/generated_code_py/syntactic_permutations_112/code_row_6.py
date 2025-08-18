from flask import Flask, request, make_response
import subprocess

app = Flask(__name__)

@app.route('/<url>/ping')
def ping(url):
    try:
        # Run the ping command and capture output
        result = subprocess.run(['ping', '-c', '4', url], capture_output=True, text=True)
        
        if result.returncode == 0:
            response_content = f"Success: {result.stdout}"
        else:
            response_content = f"Error: {result.stderr}"
    except Exception as e:
        response_content = f"Exception occurred: {str(e)}"
    
    # Return the output of ping to the browser
    return make_response(response_content, 200)

if __name__ == '__main__':
    app.run(debug=True)