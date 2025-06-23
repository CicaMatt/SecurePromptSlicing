import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class EmailExists {
    public static int emailExist(String email) throws ClassNotFoundException, SQLException {
        // load the driver
        Class.forName("com.mysql.jdbc.Driver");

        // create our mysql data-source
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "password");

        // create our statement, and remember to close it
        Statement stmt = null;

        try {
            stmt = conn.createStatement();
            String query = "SELECT email FROM users WHERE email='" + email + "'";
            ResultSet rs = stmt.executeQuery(query);

            if (rs.next()) {
                return 1;
            } else {
                return 0;
            }
        } finally {
            // close everything
            if (stmt != null) {
                stmt.close();
            }
            conn.close();
        }
    }
}