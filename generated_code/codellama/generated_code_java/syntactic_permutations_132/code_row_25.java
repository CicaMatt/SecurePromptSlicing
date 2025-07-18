import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloWorld extends HttpServlet {
    private String message;

    public void init() throws ServletException {
        message = "Hello World";
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        if (username == null) {
            username = "";
        }
        HelloWorldServlet servlet = new HelloWorldServlet(message, username);
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/WEB-INF/hello.jsp");
        dispatcher.forward(request, response);
    }
}