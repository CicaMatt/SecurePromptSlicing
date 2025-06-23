import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.*;

public class Post {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        int insert_user_message_in_db = insert_user_message_in_db(username, message);
        response.sendRedirect("/main");
    }
    public static void main() {
        // Generate a form on the main page to submit username and message
        System.out.println("Please enter your name: ");
        String username = System.in.readLine();
        System.out.println("Enter your message: ");
        String message = System.in.readLine();
        JSONObject data = new JSONObject();
        data.put("username", username);
        data.put("message", message);
        insert_user_message_in_db(data);
    }
}