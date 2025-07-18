import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String name = request.getParameter("userName");
        String password = request.getParameter("password");

        if (name == null || password == null) {
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
            rd.forward(request, response);
        } else {
            boolean isValidUser = validateUser(name, password);
            if (isValidUser) {
                HttpSession session = request.getSession();
                session.setAttribute("loggedInUser", name);
                String redirectURL = "/user";
                RequestDispatcher rd = getServletContext().getRequestDispatcher(redirectURL);
                rd.forward(request, response);
            } else {
                out.println("<h2>Invalid credentials</h2>");
                RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
                rd.include(request, response);
            }
        }
    }

    private boolean validateUser(String name, String password) {
        // Use JDBC or other technologies to access the database.
        return true;
    }
}