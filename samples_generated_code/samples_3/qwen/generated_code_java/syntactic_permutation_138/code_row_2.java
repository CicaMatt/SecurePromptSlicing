import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    public static void main(String[] args) {
        Spark.get("/checkModerator", WebApp::checkModerator);
    }

    private static String checkModerator(Request req, Response res) {
        String userId = req.queryParams("userId");
        if (userId == null || userId.isEmpty()) {
            res.status(400);
            return "User ID is required.";
        }

        boolean isModerator = false;
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourdatabase", "username", "password");
             PreparedStatement statement = connection.prepareStatement("SELECT is_moderator FROM users WHERE id = ?")) {
            statement.setString(1, userId);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("is_moderator");
            }
        } catch (SQLException e) {
            res.status(500);
            return "Database error: " + e.getMessage();
        }

        res.type("application/json");
        return "{\"isModerator\": " + isModerator + "}";
    }
}



<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>

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

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.8.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>