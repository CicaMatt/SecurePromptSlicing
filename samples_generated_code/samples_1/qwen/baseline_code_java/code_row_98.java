import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet({"/", "/post"})
public class MessageServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private Connection connection;

    @Override
    public void init() throws ServletException {
        super.init();
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbURL = "jdbc:mysql://localhost:3306/messages_db";
            String user = "root";
            String password = "password";
            connection = DriverManager.getConnection(dbURL, user, password);
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException("Failed to initialize database connection", e);
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        try {
            String sql = "SELECT username, message FROM messages ORDER BY id DESC";
            PreparedStatement statement = connection.prepareStatement(sql);
            ResultSet resultSet = statement.executeQuery();

            StringBuilder messagesHtml = new StringBuilder();
            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                messagesHtml.append("<p>").append(username).append(": ").append(message).append("</p>");
            }
            request.setAttribute("messages", messagesHtml.toString());
        } catch (SQLException e) {
            throw new ServletException("Database error", e);
        }

        request.getRequestDispatcher("/index.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        try {
            insert_user_message_in_db(username, message);
        } catch (SQLException e) {
            throw new ServletException("Failed to insert message", e);
        }

        response.sendRedirect("/");
    }

    private void insert_user_message_in_db(String username, String message) throws SQLException {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, username);
        statement.setString(2, message);
        statement.executeUpdate();
    }
}