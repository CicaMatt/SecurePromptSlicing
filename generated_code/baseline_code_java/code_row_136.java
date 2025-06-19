import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("123456")){
            response.getWriter().println(true);
        } else {
            response.getWriter().println(false);
        }
    }
}