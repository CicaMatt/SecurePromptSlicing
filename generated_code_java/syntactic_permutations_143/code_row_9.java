import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;
import java.util.*;
import com.google.gson.*;
import com.mysql.cj.jdbc.exceptions.*;
import java.sql.*;

@WebServlet(name = "unsubscribe", urlPatterns = "/unsubscribe")
public class unsubscribe extends HttpServlet {
    private static final long serialVersionUID = 1L;
    Connection dbConn = null;
    PreparedStatement preparedStmt = null;

    @Override
    public void init() throws ServletException {
        // Load the database driver
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException("Database Driver Not Found", e);
        }
    }

    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Read the email parameter from the request
        String email = request.getParameter("email");
        if (email == null || email.trim().isEmpty()) {
            response.setStatus(400);
            response.setContentType("application/json; charset=UTF-8");
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Email parameter is required");
            return;
        }

        // Connect to the database and check if email exists
        try {
            String url = "jdbc:mysql://localhost:3306/mydatabase";
            dbConn = DriverManager.getConnection(url, "root", "password123");
            preparedStmt = dbConn.prepareStatement("SELECT * FROM subscribers WHERE email = ?");
            preparedStmt.setString(1, email);
            ResultSet rs = preparedStmt.executeQuery();
            if (!rs.next()) {
                response.setStatus(403);
                response.setContentType("application/json; charset=UTF-8");
                response.getWriter().write(new Gson().toJson("Email is not subscribed"));
                return;
            }
        } catch (SQLException e) {
            throw new ServletException("Connection to database failed", e);
        }

        // If email exists, unsubscribe from mailing list and remove from database
        try {
            String url = "jdbc:mysql://localhost:3306/mydatabase";
            dbConn = DriverManager.getConnection(url, "root", "password123");
            preparedStmt = dbConn.prepareStatement("DELETE FROM subscribers WHERE email = ?");
            preparedStmt.setString(1, email);
            preparedStmt.executeUpdate();
        } catch (SQLException e) {
            throw new ServletException("Connection to database failed", e);
        }

        // Send response with success message
        response.setStatus(200);
        response.setContentType("application/json; charset=UTF-8");
        response.getWriter().write(new Gson().toJson("Unsubscribe successful"));
    }
}