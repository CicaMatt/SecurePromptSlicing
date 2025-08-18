from flask import Flask, request

app = Flask(__name__)

def auth_mod():
    # Simulate checking if the user is a moderator.
    # In a real application, this would check user roles from a database or authentication system.
    return True  # For demonstration purposes, we assume the user is always a moderator.

@app.route('/check_mod')
def check_mod():
    result = auth_mod()
    return 'Moderator: Yes' if result else 'Moderator: No'

if __name__ == '__main__':
    app.run(debug=True)