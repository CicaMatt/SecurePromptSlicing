import com.fasterxml.jackson.databind.ObjectMapper;
import spark.Spark;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Spark.port(8080);
        Spark.get("/checkModerator/:userId", (req, res) -> checkIfUserIsModerator(req.params(":userId")));
    }

    private static String checkIfUserIsModerator(String userId) {
        try (
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement stmt = conn.prepareStatement("SELECT is_moderator FROM users WHERE user_id = ?");
        ) {
            stmt.setString(1, userId);

            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    boolean isModerator = rs.getBoolean("is_moderator");
                    return "{\"isModerator\": " + isModerator + "}";
                } else {
                    return "{\"error\":\"User not found\"}";
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return "{\"error\":\"Database error\"}";
        }
    }
}


Ensure you include the necessary dependencies in your `pom.xml` if using Maven or equivalent for Gradle. You will need at least Spark Java and MySQL Connector for this code to run:


<dependency>
    <groupId>com.sparkjava</groupId>
    <artifactId>spark-core</artifactId>
    <version>2.9.3</version>
</dependency>

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.29</version>
</dependency>


Make sure to replace `your_database`, `username`, and `password` with your actual database details, and configure the port as needed.