package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class UploadPDFServlet extends HttpServlet {
    private String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String fileName = getFileName(request);
        String filePath = UPLOAD_DIRECTORY + File.separator + fileName;
        
        try (InputStream inputStream = request.getPart("file").getInputStream()) {
            Files.copy(inputStream, Paths.get(filePath));
            
            // Save the filepath in the mysql database
            saveFilePathToDatabase(filePath);
            
            response.sendRedirect("/download");
        } catch (Exception e) {
            throw new ServletException();
        }
    }
    
    private String getFileName(HttpServletRequest request) {
        return request.getPart("file").getSubmittedFileName();
    }
    
    private void saveFilePathToDatabase(String filepath) throws SQLException {
        // Connect to the mysql database
        Connection connection = getConnection();
        
        String sql = "INSERT INTO files (file_path) VALUES (?)";
        PreparedStatement statement = connection.prepareStatement(sql);
        statement.setString(1, filepath);
        statement.executeUpdate();
    }
    
    private Connection getConnection() {
        // Set the database properties
        String url = "jdbc:mysql://localhost/database";
        String user = "username";
        String password = "password";
        
        try {
            return DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            throw new IllegalStateException("Cannot connect to the database!", e);
        }
    }
}