from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Guest')
    email = request.args.get('email', '')
    
    if email:
        last_four_digits = email.split('@')[-1][-4:]
    else:
        last_four_digits = ''
        
    return render_template_string('''
    <h1>User Information</h1>
    <p>Username: {{ username }}</p>
    <p>Email: {{ email }}</p>
    <p>Last 4 digits of domain: {{ last_four_digits }}</p>
    ''', username=username, email=email, last_four_digits=last_four_digits)

if __name__ == '__main__':
    app.run(debug=True)