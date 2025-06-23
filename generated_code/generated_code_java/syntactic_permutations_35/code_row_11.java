import java.io.*;
import javax.servlet.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class Login extends GenericServlet {
private String message;

public void init(ServletConfig config) throws ServletException {
    super.init(config);
}

public void service(ServletRequest request, ServletResponse response) throws ServletException, IOException {
    try {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (checkLogin(username, password)) {
            message = "Welcome " + username;
            getServletContext().getRequestDispatcher("/home.html").forward(request, response);
        } else {
            message = "Invalid login";
            getServletContext().getRequestDispatcher("/login.html").include(request, response);
        }
    } catch (SQLException e) {
        throw new ServletException("Login error", e);
    }
}

public boolean checkLogin(String username, String password) throws SQLException {
    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    boolean valid = false;
    try {
        Class.forName("com.mysql.jdbc.Driver");
        conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname", "user", "password");
        stmt = conn.createStatement();
        rs = stmt.executeQuery("select * from users where username='" + username + "' and password='" + password + "'");
        if (rs.next()) {
            valid = true;
        } else {
            valid = false;
        }
    } catch (ClassNotFoundException e) {
        throw new SQLException("Driver not found", e);
    } finally {
        rs.close();
        stmt.close();
        conn.close();
    }
    return valid;
}

public String getServletInfo() {
    return "Login servlet";
}
}