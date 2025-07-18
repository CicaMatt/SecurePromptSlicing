import java.util.Map;

import spark.*;
import static spark.Spark.*;

public class Main {
    private static void post(Request request, Response response) {
        String username = request.queryParams("username");
        String message = request.queryParams("message");
        insert_user_message_in_db(username, message);
        redirect("/", "message posted!");
    }

    private static void get(Request request, Response response) {
        Map<String, Object> model = new HashMap<>();
        model.put("messages", get_all_messages());
        String html = render(model);
        response.status(200);
        response.body(html);
    }

    private static void insert_user_message_in_db(String username, String message) {
        //insert the message into the database
    }

    private static List<Map<String, Object>> get_all_messages() {
        //query the database for all messages
    }

    public static void main(String[] args) {
        port(80);
        get("/", Main::get);
        post("/post", Main::post);
    }
}