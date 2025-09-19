import io.javalin.Javalin;
import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {

    private static HikariDataSource dataSource;

    public static void main(String[] args) {
        initializeDatabase();

        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/check", ctx -> checkDatabase(ctx));
    }

    private static void initializeDatabase() {
        HikariConfig config = new HikariConfig();
        config.setJdbcUrl("jdbc:h2:mem:testdb;DB_CLOSE_DELAY=-1");
        config.setUsername("sa");
        config.setPassword("");
        config.addDataSourceProperty("cachePrepStmts", "true");
        config.addDataSourceProperty("prepStmtCacheSize", "250");
        config.addDataSourceProperty("prepStmtCacheSqlLimit", "2048");

        dataSource = new HikariDataSource(config);

        try (Connection connection = dataSource.getConnection()) {
            String createTableSQL = "CREATE TABLE IF NOT EXISTS Test (" +
                    "id INT AUTO_INCREMENT PRIMARY KEY, " +
                    "data VARCHAR(255) NOT NULL)";
            connection.createStatement().execute(createTableSQL);
        } catch (SQLException e) {
            throw new RuntimeException("Failed to initialize database", e);
        }
    }

    private static void checkDatabase(io.javalin.Context ctx) {
        String query = "SELECT COUNT(*) FROM Test";
        
        try (Connection connection = dataSource.getConnection();
             PreparedStatement statement = connection.prepareStatement(query);
             ResultSet resultSet = statement.executeQuery()) {

            if (resultSet.next()) {
                int count = resultSet.getInt(1);
                ctx.json("{\"message\": \"Number of records: " + count + "\"}");
            }
        } catch (SQLException e) {
            ctx.status(io.javalin.http.HttpStatus.INTERNAL_SERVER_ERROR).json("{\"error\": \"Database query failed\"}");
        }
    }
}


To run this code, you need to add the following dependencies in your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.12.0</version>
    </dependency>
    <dependency>
        <groupId>com.zaxxer</groupId>
        <artifactId>HikariCP</artifactId>
        <version>5.0.1</version>
    </dependency>
    <dependency>
        <groupId>org.h2database</groupId>
        <artifactId>h2</artifactId>
        <version>2.1.214</version>
        <scope>runtime</scope>
    </dependency>
</dependencies>


Or in your `build.gradle` if using Gradle:


dependencies {
    implementation 'io.javalin:javalin:4.12.0'
    implementation 'com.zaxxer:HikariCP:5.0.1'
    runtimeOnly 'org.h2database:h2:2.1.214'
}