package com.codenation.log;
import java.sql.*;
import javax.servlet.http.*;
public class LogPage extends HttpServlet {
    private String username, password;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        username = request.getParameter("username");
        password = request.getParameter("password");
        if (checkCredentials()) {
            redirectToDashboardPage();
        } else {
            redirectBackToLogPage();
        }
    }
    public boolean checkCredentials() {
        Connection conn;
        ResultSet rs;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/codenation", "root", "password");
            PreparedStatement ps = conn.prepareStatement("select * from users where username=? and password=?");
            ps.setString(1, username);
            ps.setString(2, password);
            rs = ps.executeQuery();
            if (rs.next()) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            System.out.println("Error: " + e);
            return false;
        }
    }
    public void redirectToDashboardPage() {
        RequestDispatcher rd = getServletContext().getRequestDispatcher("/dashboard");
        rd.forward(request, response);
    }
    public void redirectBackToLogPage() {
        RequestDispatcher rd = getServletContext().getRequestDispatcher("/log");
        rd.forward(request, response);
    }
}