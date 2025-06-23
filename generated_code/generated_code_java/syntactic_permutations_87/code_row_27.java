package com.example.demo;

import java.sql.*;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class DemoApplication {
    @RequestMapping("/temperature_for_location")
    public int temperature_for_location(@RequestParam(value = "latitude", defaultValue = "0") double latitude, 
                        @RequestParam(value = "longitude", defaultValue = "0") double longitude,
                        @RequestParam(value = "date", defaultValue = "2018-04-13") String date) {
        String url = "jdbc:mysql://localhost/weather";
        Connection con = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            con = DriverManager.getConnection(url, "root", "password");
            Statement stmt = con.createStatement();
            String query = "SELECT temperature FROM weather WHERE latitude=" + latitude 
                                +" AND longitude="+longitude+" AND date='"+date+"'";
            ResultSet rs = stmt.executeQuery(query);
            rs.next();
            return rs.getInt(1);
        }catch(Exception e){
            System.out.println("Something went wrong");
            return 0;
        }finally {
            if (con != null) {
                try {
                    con.close();
                } catch (SQLException e) {}
            }
        }
    }
}