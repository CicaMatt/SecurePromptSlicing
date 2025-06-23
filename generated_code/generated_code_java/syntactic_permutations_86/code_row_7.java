package com.example;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Temperature extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)  throws ServletException, IOException{
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");
        
        PrintWriter out = response.getWriter();
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/web_customer", "root", "secret");
            PreparedStatement statement = con.prepareStatement("SELECT max(temperature) FROM weather WHERE latitude=? and longitude=? and year=? and month=? and day=? and grib_file=?");
            statement.setString(1, latitude);
            statement.setString(2, longitude);
            statement.setString(3, year);
            statement.setString(4, month);
            statement.setString(5, day);
            statement.setString(6, grib_file);
            ResultSet result = statement.executeQuery();
            if (result.next()) {
                out.println("The maximum temperature is: " + result.getInt(1));
            } else {
                out.println("No results returned");
            }
        } catch (Exception e) {
            System.out.print(e);
        }
    }
}