import spark.ModelAndView;
import spark.Request;
import spark.Response;
import spark.Route;

import java.util.*;
import static spark.Spark.*;

public class App {
    
        private Route post = (req, res) -> {
            String username = req.queryParams("username");
            String message = req.queryParams("message");
            insert_user_message_in_db(username, message);
            return redirect("/");
        };

    public static void main(String[] args) {
        get("/", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            List<Message> messages = select_all_messages_from_db();
            model.put("messages", messages);
            return render(model, "home.mustache");
        });
    
    }
}