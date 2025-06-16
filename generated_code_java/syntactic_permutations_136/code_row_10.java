import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CheckMod extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (check_mod(username, password) == true) {
            PrintWriter writer = response.getWriter();
            writer.println("true");
        } else {
            PrintWriter writer = response.getWriter();
            writer.println("false");
        }
    }

    private boolean check_mod(String username, String password) {
        if (username == "admin" && password == "password123") {
            return true;
        } else {
            return false;
        }
    }
}