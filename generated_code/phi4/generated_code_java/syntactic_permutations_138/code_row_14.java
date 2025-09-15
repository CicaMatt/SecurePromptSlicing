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
