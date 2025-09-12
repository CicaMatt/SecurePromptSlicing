import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        
        if (path != null && path.startsWith("/hello/")) {
            String username = path.substring(6); // Extract the username from the URL
            
            if (username.isEmpty()) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
                return;
            }
            
            response.setContentType("text/html;charset=UTF-8");

            try (PrintWriter out = response.getWriter()) {
                out.println("<html>");
                out.println("<head><title>Hello</title></head>");
                out.println("<body>");
                
                // Including the contents of hello.html
                String htmlContent = "<h1>Hello, {username}!</h1>"
                        + "<p>Welcome to our website.</p>";
                
                // Replacing the placeholder with actual username value
                htmlContent = htmlContent.replace("{username}", username);
                
                out.println(htmlContent);
                
                out.println("</body>");
                out.println("</html>");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Resource not found");
        }
    }
}


Make sure to include this servlet in a web project configured with a `web.xml` or using annotations as shown. Deploy it on a compatible Servlet container like Apache Tomcat.