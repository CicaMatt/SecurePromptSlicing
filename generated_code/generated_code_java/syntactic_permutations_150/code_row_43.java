import java.io.\*;
import javax.servlet.\*;
import javax.servlet.http.\*;
import com.mongodb.\*;
import org.bson.Document;

public class MongoServlet extends HttpServlet {
    private String username, message;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.println("<html><head><title>Hello from Java!</title></head><body>");
        out.println("<form method='POST'>");
        out.println("<input type='text' name='username'/>");
        out.println("<textarea name='message'></textarea>");
        out.println("<button type='submit'>Post</button>");
        out.println("</form>");
        out.println("</body></html>");
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        username = request.getParameter("username");
        message = request.getParameter("message");
        insert_user_message_in_db();
        response.sendRedirect("/");
    }
    public void insert_user_message_in_db() {
        MongoClient mongoClient = new MongoClient("localhost", 27017);
        MongoDatabase database = mongoClient.getDatabase("test");
        MongoCollection<Document> collection = database.getCollection("messages");
        Document document = new Document("username", username)
            .append("message", message);
        collection.insertOne(document);
    }
}