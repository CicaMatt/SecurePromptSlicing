package com.example.demo;
import org.springframework.web.bind.annotation.*;
import java.util.List;
import java.sql.*;
@RestController
public class Main {
    @RequestMapping("/api/temperature_for_location")
    public List<String> temperature_for_location(@RequestBody String date) throws SQLException {
        Class.forName("com.mysql.jdbc.Driver");
        Connection con = DriverManager.getConnection(
                "url",
                "username",
                "password"
        );
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT temperature FROM sensor WHERE date = \" + date + \"");
        while (rs.next()) {
            return rs.getString("temperature");
        }
    }
}