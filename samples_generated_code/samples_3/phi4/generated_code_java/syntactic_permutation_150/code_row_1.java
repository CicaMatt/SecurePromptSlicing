import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class MessageServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        insertUserMessageInDb(username, message);

        response.sendRedirect("main.jsp");
    }

    private void insertUserMessageInDb(String username, String message) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;

        try {
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/yourDatabase", "root", "password");

            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
            preparedStatement = connection.prepareStatement(sql);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, message);

            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
</head>
<body>
    <h1>Submit a Message</h1>
    <form action="post" method="post">
        Username: <input type="text" name="username"><br><br>
        Message: <textarea name="message"></textarea><br><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/main")
public class MainServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.sendRedirect("main.jsp");
    }
}


Make sure to update the database connection parameters (`yourDatabase`, `root`, `password`) with your actual database settings. Ensure that you have a `messages` table in your database with columns `username` and `message`.