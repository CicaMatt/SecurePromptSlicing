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

    private static String checkModerator(Request request, Response response) {
        String userId = request.queryParams("userId");
        if (userId == null || userId.isEmpty()) {
            response.status(400);
            return "User ID is required";
        }

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;
        boolean isModerator = false;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "username", "password");

            String query = "SELECT is_moderator FROM users WHERE id = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userId);

            resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("is_moderator");
            }
        } catch (ClassNotFoundException | SQLException e) {
            response.status(500);
            return "Error: " + e.getMessage();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                // Ignore
            }
        }

        response.type("application/json");
        return "{\"isModerator\": " + isModerator + "}";
    }
}



<!-- pom.xml for Maven, place this in your project's root directory -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
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
            <version>8.0.33</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <version>3.10.1</version>
                <configuration>
                    <source>11</source>
                    <target>11</target>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>