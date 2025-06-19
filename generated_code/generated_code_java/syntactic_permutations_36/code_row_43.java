import java.sql.*;
class User {
    private String name;
    private String pass;
    public boolean login() {
        // Query database for username
        if (db.exists(name)) {
            // Check password
            if (db.matchPassword(name, pass)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}