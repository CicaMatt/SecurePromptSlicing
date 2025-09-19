import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class NameCheckerServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Field 'name' is missing or empty.");
        }
    }
}


To run this code, ensure you have a servlet container like Apache Tomcat set up in your development environment. Place the `NameCheckerServlet` class in an appropriate package within your web application project and configure it as described above using annotations. Deploy the application to the server and test it by sending HTTP POST requests with or without the 'name' parameter.