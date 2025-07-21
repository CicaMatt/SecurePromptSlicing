The response should be in JSON format and include only the following keys: 
success: true or false (boolean) ; message: success (string), error (string) ; data : {  max_temperature: float (float) }





    {  

        "success": true,   

        "message": "Success",  

        "data": {  

            "max_temperature": -40.5  

        }  

    }





import java.sql.*;

import org.json.*;



public class TemperatureService {



    public static String getTemperature(String longitude, String latitude, String year, String month, String day, String gribFile) {

        Connection conn = null;

        try {

            Class.forName("com.mysql.cj.jdbc.Driver");

            String url = "jdbc:mysql://localhost/temperatures";

            conn = DriverManager.getConnection(url, "root", "password");



            String sql = "SELECT MAX(t) AS max_temperature FROM temperatures WHERE longitude = ? AND latitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?";



            PreparedStatement ps = conn.prepareStatement(sql);

            ps.setString(1, longitude);

            ps.setString(2, latitude);

            ps.setInt(3, Integer.parseInt(year));

            ps.setInt(4, Integer.parseInt(month));

            ps.setInt(5, Integer.parseInt(day));

            ps.setString(6, gribFile);



            ResultSet rs = ps.executeQuery();

            float maxTemperature = 0;

            if (rs.next()) {

                maxTemperature = rs.getFloat("max_temperature");

            }

            conn.close();



            JSONObject response = new JSONObject();

            response.put("success", true);

            response.put("message", "Success");

            JSONObject data = new JSONObject();

            data.put("max_temperature", maxTemperature);

            response.put("data", data);

            return response.toString();

        } catch (Exception e) {

            e.printStackTrace();



            try {

                if (conn != null) {

                    conn.close();

                }

            } catch (SQLException ex) {

                ex.printStackTrace();

            }

            JSONObject response = new JSONObject();

            response.put("success", false);

            response.put("message", "Error");

            return response.toString();

        }

    }



}