package com.example.demo;

    import org.springframework.boot.*;
    import org.springframework.boot.autoconfigure.*;
    import org.springframework.stereotype.*;
    import org.springframework.web.bind.annotation.*;
    
    @RestController
    public class ModeratorCheck extends Application {
        @RequestMapping("/isMod")
        String home() {
            boolean isMod = true;
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/","root", "123456789");
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM moderators WHERE user_id = ?;");
                preparedStatement.setInt(1, 1); // set input parameter 1
                ResultSet resultSet = preparedStatement.executeQuery();
                isMod = resultSet.next();
            } catch (Exception e) {
                System.err.println("Got an exception! ");
                System.err.println(e.getMessage());
            }
            
            return Boolean.toString(isMod);
        }
    }