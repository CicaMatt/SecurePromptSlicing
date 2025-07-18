import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
public class check_mod extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String session = request.getSession().getId();
        if (auth_mod(username, password, session)) {
            response.sendRedirect("/admin.jsp");
        } else {
            response.sendRedirect("/login.html");
        }
    }
}