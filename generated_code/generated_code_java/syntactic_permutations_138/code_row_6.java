package com.example;
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.sql.*;
public class UserServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String userId = request.getParameter("userId");
        boolean isModerator;
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", "username", "password")) {
            Statement statement = connection.createStatement();
            String query = "SELECT moderator FROM users WHERE id = " + userId;
            ResultSet resultSet = statement.executeQuery(query);
            if (resultSet.next()) {
                isModerator = resultSet.getBoolean("moderator");
            } else {
                response.sendError(404, "User not found");
                return;
            }
        } catch (SQLException e) {
            throw new ServletException(e);
        }
        response.setContentType("application/json");
        response.getWriter().write("{\"isModerator\": " + isModerator + "}");
    }
}