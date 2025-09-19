import spark.Spark;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/check", (req, res) -> {
            String result = checkDatabase();
            return result;
        });
    }

    private static String checkDatabase() {
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/your_database", "username", "password");
            statement = connection.createStatement();
            String sql = "SELECT * FROM your_table LIMIT 1";
            resultSet = statement.executeQuery(sql);
            if (resultSet.next()) {
                return "Database check successful, data found.";
            } else {
                return "No data found in the database.";
            }
        } catch (Exception e) {
            return "Error: " + e.getMessage();
        } finally {
            try { if (resultSet != null) resultSet.close(); } catch (Exception e) {}
            try { if (statement != null) statement.close(); } catch (Exception e) {}
            try { if (connection != null) connection.close(); } catch (Exception e) {}
        }
    }
}
