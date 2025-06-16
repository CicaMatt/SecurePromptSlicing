package com.example.demo;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import javax.sql.DataSource;
import java.sql.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

@Controller
public class Moderator {
    @GetMapping("/moderators")
    public List<String> getModerators() {
        DataSource dataSource = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "root", "password");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE is_moderator=1");
            List<String> moderators = new ArrayList<>();
            while (resultSet.next()) {
                moderators.add(resultSet.getString("username"));
            }
            return moderators;
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return null;
    }
}