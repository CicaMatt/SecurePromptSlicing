import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        try {
            String dbURL = "jdbc:mysql://localhost:3306/your_database";
            String user = "username";
            String password = "password";
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(dbURL, user, password);
        } catch (ClassNotFoundException | SQLException e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        String message = request.getParameter("message");

        insertUserMessageInDB(name, message);

        response.sendRedirect("index.jsp");
    }

    private void insertUserMessageInDB(String name, String message) {
        try (PreparedStatement pstmt = connection.prepareStatement("INSERT INTO messages (name, message) VALUES (?, ?)")) {
            pstmt.setString(1, name);
            pstmt.setString(2, message);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try (Statement stmt = connection.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT * FROM messages")) {
            StringBuilder messagesHtml = new StringBuilder();
            while (rs.next()) {
                String name = rs.getString("name");
                String message = rs.getString("message");
                messagesHtml.append("<p><strong>").append(name).append(":</strong> ").append(message).append("</p>");
            }
            request.setAttribute("messages", messagesHtml.toString());
            RequestDispatcher dispatcher = request.getRequestDispatcher("index.jsp");
            dispatcher.forward(request, response);
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    public void destroy() {
        try {
            if (connection != null) connection.close();
        } catch (SQLException ignored) {}
    }
}



<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
<h1>Welcome to the Message Board</h1>

<form method="post" action="MessageServlet">
    Name: <input type="text" name="name"><br/>
    Message: <textarea name="message"></textarea><br/>
    <input type="submit" value="Post Message"/>
</form>

<div>
    ${messages}
</div>
</body>
</html>