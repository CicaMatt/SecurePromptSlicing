import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        post("/post", (request, response) -> {
            String username = request.queryParams("username");
            String message = request.queryParams("message");

            insertUserMessageInDb(username, message);

            response.redirect("/");
            return null;
        });
    }

    private static void insertUserMessageInDb(String username, String message) {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_db_user";
        String password = "your_db_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                pstmt.setString(2, message);
                pstmt.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Ensure you have the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.28</version>
    </dependency>
</dependencies>