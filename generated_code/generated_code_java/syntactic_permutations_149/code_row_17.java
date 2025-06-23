import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;
import static spark.Spark.*;
import java.sql.*;
public class HelloWorld {
    public static void main(String[] args) throws Exception {
        post("/post", new Route() {
            @Override
            public Object handle(Request request, Response response) {
                String user = request.queryParams("user");
                String message = request.queryParams("message");
                insert_user_message_in_db(user, message);
                response.redirect("/");
                return "success";
            }
        });
    }
}