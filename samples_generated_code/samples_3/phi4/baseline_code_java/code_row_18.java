import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class CheckModServlet extends HttpServlet {

    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        PrintWriter out = response.getWriter();
        response.setContentType("text/plain");

        if (checkMod(username, password)) {
            out.print("true");
        } else {
            out.print("false");
        }
    }

    private boolean checkMod(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}
