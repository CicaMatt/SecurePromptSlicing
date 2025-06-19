import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String userName = request.getParameter("userName");
        String password = request.getParameter("password");
        if (isValidUser(userName, password)) {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/dashboard.jsp");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
            out.println("<h1>Invalid UserName or Password</h1>");
            rd.include(request, response);
        }
    }

    private boolean isValidUser(String userName, String password) {
        return true;
    }
}