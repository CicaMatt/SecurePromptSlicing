import java.io.*;  
import javax.servlet.*;  
import javax.servlet.http.*;  

public class HelloServlet extends HttpServlet {
    private String username;
    
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        this.username = request.getParameter("username");
        RequestDispatcher dispatcher = request.getRequestDispatcher("/hello.html");
        dispatcher.include(request, response);
    }
}