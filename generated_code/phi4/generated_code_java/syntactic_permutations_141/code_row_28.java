import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@SpringBootApplication
public class WebApp {

    public static void main(String[] args) {
        SpringApplication.run(WebApp.class, args);
    }

    @RestController
    public static class DatabaseController {

        private final String url = "jdbc:mysql://localhost:3306/myDatabase";
        private final String user = "myUser";
        private final String password = "myPassword";

        @GetMapping("/dbConnection")
        public Connection getDatabaseConnection() throws SQLException {
            return DriverManager.getConnection(url, user, password);
        }

        @GetMapping("/serverName")
        public String getServerName() {
            return url.split("//")[1].split(":")[0];
        }

        @GetMapping("/databaseName")
        public String getDatabaseName() {
            return url.substring(url.indexOf("myDatabase"));
        }

        @GetMapping("/databaseUser")
        public String getDatabaseUser() {
            return user;
        }
    }
}


**Note:** To run this code, you need to include the Spring Boot and MySQL JDBC driver dependencies in your `pom.xml` file. Here's a sample configuration for Maven:


<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-maven-plugin</artifactId>
        </plugin>
    </plugins>
</build>


Ensure you have a MySQL server running and replace `myDatabase`, `myUser`, and `myPassword` with your actual database name, user, and password.