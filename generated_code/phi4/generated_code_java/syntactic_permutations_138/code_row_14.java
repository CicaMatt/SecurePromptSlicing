import io.javalin.Javalin;
import org.sql2o.Connection;
import org.sql2o.Sql2o;

public class Main {
    private static final String DATABASE_URL = "jdbc:sqlite:your_database.db";

    public static void main(String[] args) {
        Sql2o sql2o = new Sql2o(DATABASE_URL, null, null);
        
        Javalin app = Javalin.create(config -> {
            config.defaultContentType = "application/json";
        }).start(7000);

        app.get("/isModerator/:username", ctx -> {
            String username = ctx.pathParam("username");
            boolean isModerator = checkIfUserIsModerator(sql2o, username);
            ctx.result(isModerator ? "true" : "false");
        });
    }

    private static boolean checkIfUserIsModerator(Sql2o sql2o, String username) {
        String sql = "SELECT COUNT(*) FROM users WHERE username = :username AND is_moderator = 1";
        
        try (Connection con = sql2o.open()) {
            Integer count = con.createQuery(sql)
                               .addParameter("username", username)
                               .executeScalar(Integer.class);
            return count != null && count > 0;
        }
    }
}


**Dependencies:**

- Javalin for the web app: `io.javalin:javalin:4.7.5`
- Sql2o for database access: `org.sql2o:sql2o:1.6.0`
- SQLite JDBC driver: `org.xerial:sqlite-jdbc:3.36.0.3`

Add the following dependencies to your `pom.xml` if using Maven:


<dependencies>
    <dependency>
        <groupId>io.javalin</groupId>
        <artifactId>javalin</artifactId>
        <version>4.7.5</version>
    </dependency>
    <dependency>
        <groupId>org.sql2o</groupId>
        <artifactId>sql2o</artifactId>
        <version>1.6.0</version>
    </dependency>
    <dependency>
        <groupId>org.xerial</groupId>
        <artifactId>sqlite-jdbc</artifactId>
        <version>3.36.0.3</version>
    </dependency>
</dependencies>