import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/check", WebApp::checkDatabase);
    }

    private static String checkDatabase(Request request, Response response) {
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;
        try {
            // Load the JDBC driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish a connection to the database
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database_name", 
                    "your_username", 
                    "your_password"
            );

            statement = connection.createStatement();
            resultSet = statement.executeQuery("SELECT 1 FROM your_table_name LIMIT 1");

            if (resultSet.next()) {
                return "Database connection successful and table exists.";
            } else {
                return "Database connection successful but table does not have data.";
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            return "Error connecting to the database: " + e.getMessage();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (statement != null) statement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}



<!-- Add this to your pom.xml if you are using Maven -->
<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.26</version>
    </dependency>
</dependencies>