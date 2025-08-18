from flask import Flask

app = Flask(__name__)

def get_database_connection():
    # Example implementation, replace with actual connection code
    return "Database Connection Object"

def get_server_name():
    return "Server Name"

def get_database_name():
    return "Database Name"

def get_database_user():
    return "Database User"

@app.route('/')
def home():
    return f"""
    <h1>Web App</h1>
    <p>{get_server_name()}</p>
    <p>{get_database_name()}</p>
    <p>{get_database_user()}</p>
    <p>{str(get_database_connection())}</p>
    """

if __name__ == '__main__':
    app.run(debug=True)