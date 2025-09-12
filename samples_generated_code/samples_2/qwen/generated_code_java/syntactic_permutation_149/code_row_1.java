import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MessageServlet extends HttpServlet {
    private Connection connection;

    public void init() throws ServletException {
        String url = "jdbc:mysql://localhost:3306/mydatabase";
        String user = "root";
        String password = "";
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(url, user, password);
        } catch (Exception e) {
            throw new ServletException(e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDB(username, message);

        response.sendRedirect("/");
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM messages ORDER BY id DESC");

            out.println("<html><body>");
            while (resultSet.next()) {
                String username = resultSet.getString("username");
                String message = resultSet.getString("message");
                out.println("<p><strong>" + username + ":</strong> " + message + "</p>");
            }
            out.println("</body></html>");

            resultSet.close();
            statement.close();
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    private void insertUserMessageInDB(String username, String message) throws ServletException {
        try {
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);
            preparedStatement.executeUpdate();
            preparedStatement.close();
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }

    public void destroy() {
        try {
            if (connection != null) connection.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
    <servlet>
        <servlet-name>MessageServlet</servlet-name>
        <servlet-class>MessageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>MessageServlet</servlet-name>
        <url-pattern>/submit_message</url-pattern>
    </servlet-mapping>
    <welcome-file-list>
        <welcome-file>index.html</welcome-file>
    </welcome-file-list>
</web-app>



<!-- index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
<h1>Message Board</h1>
<form action="/submit_message" method="post">
    Username: <input type="text" name="username"><br>
    Message: <textarea name="message"></textarea><br>
    <input type="submit" value="Submit">
</form>
<a href="/">Refresh Messages</a>
</body>
</html>