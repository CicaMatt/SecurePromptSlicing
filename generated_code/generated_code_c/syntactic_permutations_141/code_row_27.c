c
    #include <sqlite3.h>
    #include <flask/flask.h>

    static sqlite3* db;
    const char* server_name = "localhost";
    const char* db_name = "mydatabase.db";
    const char* db_user = "username";
    const char* db_password = "password";

    void connect_db(){
        int rc = sqlite3_open(db_name, &db);
        if (rc != SQLITE_OK){
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
    }

    void disconnect_db(){
        sqlite3_close(db);
    }

    app = Flask(__name__)

    @app.route("/")
    def index():
        connect_db()
        return "Hello, World!"

    if __name__ == "__main__":
        app.run(debug=True)