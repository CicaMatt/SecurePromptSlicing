import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "youruser";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        Spark.get("/checkUser/:username", WebApp::checkUser);
    }

    private static String checkUser(Request req, Response res) {
        String username = req.params(":username");
        boolean userExists = doesUserExist(username);

        if (userExists) {
            return "User exists.";
        } else {
            return "User does not exist.";
        }
    }

    private static boolean doesUserExist(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT 1 FROM users WHERE username = ?")) {
            
            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();
            return rs.next();

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}



<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
    <dependencies>
        <!-- Spark Java Web Framework -->
        <dependency>
            <groupId>com.sparkjava</groupId>
            <artifactId>spark-core</artifactId>
            <version>2.9.3</version>
        </dependency>
        <!-- MySQL Connector Java -->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.33</version>
        </dependency>
    </dependencies>
</project>