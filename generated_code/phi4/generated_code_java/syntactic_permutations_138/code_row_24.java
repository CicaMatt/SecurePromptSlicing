import io.javalin.Javalin;
import io.javalin.http.Context;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {}).start(7000);

        app.get("/checkUser", WebApp::checkUser);
    }

    public static void checkUser(Context ctx) {
        String username = ctx.queryParam("username");
        
        if (username == null || username.isEmpty()) {
            ctx.status(400).result("Username is required");
            return;
        }

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE username = ?";
            
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        ctx.status(200).result("User found");
                    } else {
                        ctx.status(404).result("User not found");
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            ctx.status(500).result("Internal Server Error");
        }
    }
}


**Dependencies to include in your `pom.xml` for Maven:**


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>5.3.1</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.27</version>
    </dependency>
</dependencies>


**Replace `your_database`, `your_username`, and `your_password` with your actual database details.**