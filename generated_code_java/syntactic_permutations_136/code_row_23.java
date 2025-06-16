import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class CheckMod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username == "admin" && password == "admin"){
            PrintWriter out = response.getWriter();
            out.println("true");
        }
    }
}