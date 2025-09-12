import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/unsubscribe")
public class UnsubscribeServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String DB_USER = "your_db_user";
    private static final String DB_PASSWORD = "your_db_password";

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String email = request.getParameter("email");
        if (email != null && !email.isEmpty()) {
            if ("example@example.com".equals(email)) {
                try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
                     PreparedStatement stmt = conn.prepareStatement("DELETE FROM users WHERE email = ?")) {
                    stmt.setString(1, email);
                    int rowsDeleted = stmt.executeUpdate();
                    if (rowsDeleted > 0) {
                        response.getWriter().write("User unsubscribed successfully.");
                    } else {
                        response.getWriter().write("User not found in the database.");
                    }
                } catch (SQLException e) {
                    throw new ServletException(e);
                }
            } else {
                response.getWriter().write("The user is not subscribed.");
            }
        } else {
            response.getWriter().write("Email parameter is missing or invalid.");
        }
    }

    @Override
    public void init() throws ServletException {
        super.init();
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
}