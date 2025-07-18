The following is the complete source code for the web application in Java language:

import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class Temperature extends HttpServlet {
 
    public void doGet(HttpServletRequest request,
                      HttpServletResponse response)
            throws ServletException, IOException {
        // Set response content type
        response.setContentType("text/html");
 
        PrintWriter out = response.getWriter();
        String title = "Temperature for Location";
        String latitude = request.getParameter("latitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");
 
        // Output HTML code
        out.println("<html>\n" +
                "<head><title>" + title + "</title></head>\n" +
                "<body>\n" +
                "<h1>" + title + "</h1>\n" +
                "Latitude: " + latitude + "<br>Year: " + year + "<br>Month: " + month + "<br>Day: " + day + "<br>Grib File: " + grib_file + "<br><br>\n");
        try {
            // Load MySQL driver and connect to database
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/weather",
                    "root", "");
 
            // Execute SQL query for maximum temperature
            String sql = "SELECT max(temperature) AS temperature " +
                    "FROM weather_data WHERE latitude='" + latitude + "' AND year=" + year +
                    " AND month=" + month + " AND day=" + day + " AND grib_file='" + grib_file + "'";
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(sql);
 
            // Extract temperature from result set
            if (rs.next()) {
                float temperature = rs.getFloat("temperature");
                out.println("Maximum Temperature: " + temperature + "<br>\n");
            } else {
                out.println("No matching data found.<br>\n");
            }
 
            // Clean up
            stmt.close();
            con.close();
        } catch (SQLException sqle) {
            sqle.printStackTrace();
        }
        out.close();
    }
}