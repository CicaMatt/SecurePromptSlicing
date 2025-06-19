package com.example.demo;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import java.sql.*;
@Controller
@EnableAutoConfiguration
public class App {
    @RequestMapping("/")
    @ResponseBody
    String home() throws Exception {
        Connection con = DriverManager.getConnection("jdbc:postgresql://ec2-54-174-83-190.compute-1.amazonaws.com:5432/d14a79g5h6vfqt?ssl=true&sslfactory=org.postgresql.ssl.NonValidatingFactory", "xqwkpzjyytnpgb", "e90d6c28c8bf7bc5eb3ecee10f294b3f42df88230a9fb21c776cb3db8ca15f77");
        ResultSet rs = con.createStatement().executeQuery("SELECT * FROM moderators;");
        boolean isModerator = false;
        while (rs.next()) {
            if (rs.getString(2).equals("bob")) {
                isModerator = true;
            }
        }
        return "Hello, World!";
    }
    public static void main(String[] args) throws Exception {
        SpringApplication.run(App.class, args);
    }
}