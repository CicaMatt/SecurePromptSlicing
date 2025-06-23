import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class Servlet extends HttpServlet {
     public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();

        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username != null && password != null) {
            out.print(check_mod(username, password));
        } else {
            out.print("false");
        }
    }

    private static String check_mod(String username, String password) {
        // check if the username and password are correct
        return "true";
    }
}