import java.io.\*;
import java.util.\*;

public class Post {
    public static void post(Request request, Response response) {
        String username = request.get("username");
        String message = request.get("message");
        insert_user_message_in_db(username, message);
        response.redirect("/main");
    }

    public static void main() {
        Request request;
        Response response;
        List<String> messages = new ArrayList<>();
        while (true) {
            if (request.getMethod().equalsIgnoreCase("POST")) {
                post(request, response);
            } else {
                for (String message : messages) {
                    System.out.println(message);
                }
            }
        }
    }

    public static void insert_user_message_in_db(String username, String message) {
        // code to insert the username and message in database goes here
    }
}