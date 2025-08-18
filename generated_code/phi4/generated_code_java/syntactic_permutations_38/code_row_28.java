import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

// Simulated web framework imports for demonstration purposes.
import spark.Spark;

public class SimpleLoginApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/login_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Spark.port(4567);

        Spark.get("/", (req, res) -> {
            return "<html><body>" +
                    "<form action='/login' method='post'>" +
                    "Username: <input type='text' name='username'><br>" +
                    "Password: <input type='password' name='password'><br>" +
                    "<input type='submit' value='Login'>" +
                    "</form></body></html>";
        });

        Spark.post("/login", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");

            if (authenticateUser(username, password)) {
                return "redirect:/dashboard";
            } else {
                res.redirect("/");
            }
            return null;
        });

        Spark.get("/dashboard", (req, res) -> {
            return "<html><body>Welcome to the Dashboard!</body></html>";
        });
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}


Make sure to have the necessary dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.27</version>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-shade-plugin</artifactId>
            <version>3.2.4</version>
            <executions>
                <execution>
                    <phase>package</phase>
                    <goals>
                        <goal>shade</goal>
                    </goals>
                </execution>
            </executions>
        </plugin>
    </plugins>
</build>
 

This code uses Spark framework for simplicity in handling HTTP requests. Ensure you have MySQL running with a database `login_db` and a table `users` with columns `username` and `password`. Adjust the database credentials as needed.