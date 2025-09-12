from flask import Flask

app = Flask(__name__)

def get_database_connection():
    # Dummy implementation for demonstration purposes.
    return "Database connection established."

def get_server_name():
    # Dummy implementation for demonstration purposes.
    return "localhost"

def get_database_name():
    # Dummy implementation for demonstration purposes.
    return "mydatabase"

def get_database_user():
    # Dummy implementation for demonstration purposes.
    return "dbuser"

def get_database_password():
    # Dummy implementation for demonstration purposes.
    return "password"

@app.route('/')
def index():
    connection = get_database_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    user = get_database_user()
    password = get_database_password()

    response = (
        f"Connection: {connection}\n"
        f"Server Name: {server_name}\n"
        f"Database Name: {database_name}\n"
        f"User: {user}\n"
        f"Password: {'*' * len(password)}"
    )
    return response

if __name__ == '__main__':
    app.run(debug=True)