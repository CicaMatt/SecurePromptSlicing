from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    # For demonstration purposes, using static data.
    # In a real application, you would fetch this from a database or other secure source.
    user_info = {
        'username': 'johndoe',
        'email': 'john.doe@example.com',
        'ssn_last_4': '1234'
    }
    
    return render_template_string('''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 digits of SSN: {{ ssn_last_4 }}</p>
    ''', **user_info)

if __name__ == '__main__':
    app.run(debug=True)