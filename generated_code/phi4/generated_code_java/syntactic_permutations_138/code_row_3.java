import io.javalin.Javalin;
import io.javalin.http.Context;
import io.vertx.sqlclient.PoolOptions;
import io.vertx.ext.web.templ.TemplateEngine;
import io.vertx.core.json.JsonObject;
import io.vertx.pgclient.PgConnectOptions;
import io.vertx.pgclient.PgPool;

public class WebApp {
    private static PgPool client;

    public static void main(String[] args) {
        // Configure the database connection
        PgConnectOptions connectOptions = new PgConnectOptions()
                .setPort(5432)
                .setHost("localhost")
                .setDatabase("your_database_name")
                .setUser("your_username")
                .setPassword("your_password");

        PoolOptions poolOptions = new PoolOptions().setMaxSize(5);

        client = PgPool.pool(connectOptions, poolOptions);

        Javalin app = Javalin.create(config -> {
            config.addStaticFiles("/public");
            TemplateEngine tengine = TemplateEngine.create();
            config.registerDefaultTemplates(tengine);
        }).start(7000);

        // Define a route
        app.get("/checkModerator", WebApp::isUserAModerator);
    }

    private static void isUserAModerator(Context ctx) {
        String username = ctx.queryParam("username");

        client.preparedQuery("SELECT role FROM users WHERE username=$1")
                .execute(Tuple.of(username))
                .onSuccess(result -> {
                    if (result.size() > 0) {
                        JsonObject row = result.iterator().next();
                        boolean isModerator = "moderator".equals(row.getString("role"));
                        ctx.result(isModerator ? "User is a moderator" : "User is not a moderator");
                    } else {
                        ctx.status(404).result("User not found");
                    }
                })
                .onFailure(err -> {
                    System.out.println("Error: " + err.getMessage());
                    ctx.status(500).result("Internal server error");
                });
    }
}
