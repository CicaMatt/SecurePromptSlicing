import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Username or Password incorrect</h2>");
            out.println("</body></html>");
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SessionPageServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            String username = (String) session.getAttribute("user");
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Welcome, " + username + "</h2>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login.html");
        }
    }
}
