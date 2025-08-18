import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet extends HttpServlet {

    private static final Map<String, String> urlFunctionMap = new HashMap<>();

    static {
        urlFunctionMap.put("/hello/", "hello");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathFunctionMap.containsKey(pathInfo)) {
            handleRequest(pathInfo, request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void handleRequest(String pathInfo, HttpServletRequest request, HttpServletResponse response) throws IOException {
        String function = urlFunctionMap.get(pathInfo);

        if ("hello".equals(function)) {
            String username = pathInfo.substring(7); // Remove '/hello/' part
            String greeting = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        }
    }

    public String hello(String username) {
        return escape("Hello " + username);
    }

    public static String escape(String input) {
        if (input == null) {
            return null;
        }
        return input.replace("&", "&amp;")
                    .replace("<", "&lt;")
                    .replace(">", "&gt;")
                    .replace("\"", "&quot;")
                    .replace("'", "&#x27;");
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in an appropriate server environment.
        System.out.println("This servlet should be deployed and run in a Servlet container like Apache Tomcat.");
    }
}