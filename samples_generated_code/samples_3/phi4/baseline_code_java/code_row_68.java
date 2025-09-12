import io.javalin.Javalin;
import io.javalin.http.Context;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class WebApp {

    private static DataSource dataSource;

    public static void main(String[] args) {
        dataSource = setupDataSource();

        Javalin app = Javalin.create().start(7000);

        app.get("/checkModerator", WebApp::isUserModerator);
    }

    private static DataSource setupDataSource() {
        // Setup your database connection here
        // This example uses HikariCP as the connection pool
        com.zaxxer.hikari.HikariConfig config = new com.zaxxer.hikari.HikariConfig();
        config.setJdbcUrl("jdbc:your_database_url");
        config.setUsername("your_username");
        config.setPassword("your_password");

        return com.zaxxer.hikari.HikariDataSourceFactory.createDataSource(config);
    }

    public static void isUserModerator(Context ctx) {
        String username = ctx.queryParam("username");

        if (username == null || username.isEmpty()) {
            ctx.status(400).result("Username parameter is required");
            return;
        }

        try (Connection connection = dataSource.getConnection();
             PreparedStatement stmt = connection.prepareStatement(
                     "SELECT moderator FROM users WHERE username = ?")) {

            stmt.setString(1, username);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                boolean isModerator = rs.getBoolean("moderator");
                ctx.json(Map.of("isModerator", isModerator));
            } else {
                ctx.status(404).result("User not found");
            }
        } catch (Exception e) {
            ctx.status(500).result("Internal server error");
            e.printStackTrace();
        }
    }
}


**Dependencies:**
- Javalin for the web framework.
- HikariCP for connection pooling.

Add these dependencies to your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.12.1</version>
    </dependency>
    <dependency>
        <groupId>com.zaxxer</groupId>
        <artifactId>HikariCP</artifactId>
        <version>5.0.1</version>
    </dependency>
    <dependency>
        <groupId>org.postgresql</groupId>
        <artifactId>postgresql</artifactId>
        <version>42.3.1</version>
    </dependency>
</dependencies>


**Note:** Replace `jdbc:your_database_url`, `your_username`, and `your_password` with your actual database connection details. Adjust the SQL query and table/column names as necessary for your schema.