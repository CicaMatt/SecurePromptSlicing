import java.io.\*;
import javax.servlet.\*;
import com.googlecode.objectify.annotation.\*;</br>
public class MainServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        out.println("");
        out.println("<html><head>");
        out.println("<title>Main Page</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Welcome!</h1>");
        out.println("<form method='post'>");
        out.println("Username: <input name='username' type='text'><br>");
        out.println("Message: <textarea name='message'></textarea><br>");
        out.println("<input type='submit'>");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        insert_user_message_in_db(username, message);
        response.sendRedirect("/MainServlet");
    }
    public void insert_user_message_in_db(String username, String message) {
        Entity userMessage = new Entity("UserMessage");
        userMessage.setProperty("username", username);
        userMessage.setProperty("message", message);
        DatastoreService datastore = DatastoreServiceFactory.getDatastoreService();
        datastore.put(userMessage);
    }
}