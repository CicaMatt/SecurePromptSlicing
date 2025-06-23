package login;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login extends HttpServlet {

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String user = request.getParameter("username");
        String pass = request.getParameter("password");
        if (user.equals("admin") && pass.equals("password")) {
            // session page
            RequestDispatcher rd = getServletContext().getRequestDispatcher("/session");
            rd.forward(request, response);
        } else {
            PrintWriter out = response.getWriter();
            out.print("Username or password is incorrect.");
        }
    }
}