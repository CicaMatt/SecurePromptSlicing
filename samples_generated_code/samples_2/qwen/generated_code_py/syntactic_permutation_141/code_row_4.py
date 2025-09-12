from flask import Flask

app = Flask(__name__)

def get_db_connection():
    # This is a placeholder for actual database connection logic
    return "Database Connection"

def get_database_name():
    return "example_db"

def get_database_user():
    return "user"

def get_database_password():
    return "password"

@app.route('/')
def index():
    conn = get_db_connection()
    db_name = get_database_name()
    db_user = get_database_user()
    db_password = get_database_password()
    return f"Connection: {conn}, Database: {db_name}, User: {db_user}, Password: {db_password}"

if __name__ == '__main__':
    app.run(debug=True)