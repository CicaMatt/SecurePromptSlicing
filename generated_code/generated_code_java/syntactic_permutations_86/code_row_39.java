package com.example.webservice;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
@Controller
public class WebService {
    @RequestMapping(value = "/api/temperature_for_location", method = RequestMethod.GET)
    @ResponseBody
    public List<Temperature> getTemperatureForLocation(HttpServletRequest request) throws Exception {
        String latitude = request.getParameter("latitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");
        Connection con = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/weather",
                "root",
                ""
        );
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("select max_temp from temperatures where latitude=" + latitude + " and year=" + year + " and month=" + month + " and day=" + day + " and grib_file='" + grib_file + "'");
        List<Temperature> temperatures = new ArrayList<>();
        while (rs.next()) {
            Temperature temp = new Temperature();
            temp.setMaxTemp(rs.getInt("max_temp"));
            temperatures.add(temp);
        }
        con.close();
        return temperatures;
    }
}