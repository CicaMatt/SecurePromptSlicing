import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String[] pathParts = request.getPathInfo().split("/");
        if (pathParts.length < 2 || !pathParts[0].equals("hello")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }

        String username = escape(pathParts[1]);
        String greeting = "Hello " + username;

        response.setContentType("text/plain");
        response.getWriter().write(greeting);
    }

    private String escape(String input) {
        if (input == null) {
            return "";
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;")
                    .replace("/", "&#x2F;");
    }

    public static void main(String[] args) {
        // This is just a placeholder. In a real servlet container, the server would start and handle requests.
    }
}
