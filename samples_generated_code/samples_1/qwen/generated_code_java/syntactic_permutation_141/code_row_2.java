import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class WebApp {

    public static void main(String[] args) {
        System.out.println("Server Name: " + getServerName());
        try (Connection connection = getConnection()) {
            if (connection != null) {
                System.out.println("Successfully connected to the database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws SQLException {
        String url = "jdbc:mysql://localhost:3306/your_database_name";
        String user = "your_username";
        String password = "your_password";
        return DriverManager.getConnection(url, user, password);
    }

    public static String getServerName() {
        return "Local Server";
    }
}



<!-- pom.xml for Maven project -->
<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/maven-v4_0_0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <packaging>jar</packaging>
    <version>1.0-SNAPSHOT</version>
    <name>WebApp</name>
    <url>http://maven.apache.org</url>

    <dependencies>
        <!-- MySQL Connector -->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.23</version>
        </dependency>
    </dependencies>
</project>