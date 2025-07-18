import spark.Request;
import spark.Response;
import spark.Route;

public class PostRoute extends Route {
    @Override
    public Object handle(Request request, Response response) throws Exception {
        String username = request.queryParams("username");
        String message = request.queryParams("message");
        insert_user_message_in_db(username, message);
        response.redirect("/");
        return null;
    }

    private void insert_user_message_in_db(String username, String message) {
        // your logic here to store the username and message in a database
    }
}