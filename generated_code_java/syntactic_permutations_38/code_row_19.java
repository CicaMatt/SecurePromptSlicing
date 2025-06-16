Here is the complete source code for a simple login page that takes a username and password from the user and checks it against the database. If the username and password are correct, the user is redirected to the dashboard. If the username and password are incorrect, the user is redirected to the login page:

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try {
            // Load database driver
            Class.forName("com.mysql.jdbc.Driver");
            // Create connection to database
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost/mydb", "root", "");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
            if (rs.next()) {
                response.sendRedirect("dashboard.jsp");
            } else {
                request.setAttribute("errorMessage", "Invalid credentials");
                RequestDispatcher rd = getServletContext().getRequestDispatcher("/login.jsp");
                rd.forward(request, response);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}