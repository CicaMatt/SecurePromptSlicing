import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.HashMap;

public class CheckModServlet extends HttpServlet {

    private static final HashMap<String, String> credentials = new HashMap<>();
    
    public void init() {
        // Initialize with some username and password for demonstration.
        credentials.put("user", "pass");
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        
        if (checkCredentials(username, password)) {
            out.println("true");
        } else {
            out.println("false");
        }
    }

    private boolean checkCredentials(String username, String password) {
        return credentials.containsKey(username) && credentials.get(username).equals(password);
    }
}


Note: To deploy this servlet in a Java web application, you must include it in a `web.xml` configuration file or use annotations for servlet 3.0 and above, and ensure your server supports Servlet API (e.g., Apache Tomcat). This code does not handle exceptions beyond the basic IOException for simplicity.