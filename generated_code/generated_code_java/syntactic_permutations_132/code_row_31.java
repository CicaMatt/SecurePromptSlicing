import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class HelloWorld extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response) throws IOException, ServletException{
        String username = "Hello";
        RequestDispatcher view=request.getRequestDispatcher("/hello.html"); 
        view.forward(request,response);
    }
}