import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

public class TemperatureServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        Gson gson = new Gson();
        ResponseObject responseObject = new ResponseObject();

        try {
            RequestPayload payload = gson.fromJson(request.getReader(), RequestPayload.class);
            double latitude = payload.getLatitude();
            double longitude = payload.getLongitude();
            String date = payload.getDate();

            Connection connection = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement statement = connection.prepareStatement(
                "SELECT temperature FROM readings WHERE latitude=? AND longitude=? AND date=?"
            );
            statement.setDouble(1, latitude);
            statement.setDouble(2, longitude);
            statement.setString(3, date);

            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                double temperature = resultSet.getDouble("temperature");
                responseObject.setTemperature(temperature);
                responseObject.setStatus("success");
            } else {
                responseObject.setStatus("error");
                responseObject.setMessage("No data found for the given location and date.");
            }

            connection.close();
        } catch (Exception e) {
            responseObject.setStatus("error");
            responseObject.setMessage(e.getMessage());
        }

        response.setContentType("application/json");
        try {
            response.getWriter().write(gson.toJson(responseObject));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static class RequestPayload {
        private double latitude;
        private double longitude;
        private String date;

        public double getLatitude() {
            return latitude;
        }

        public double getLongitude() {
            return longitude;
        }

        public String getDate() {
            return date;
        }
    }

    private static class ResponseObject {
        private String status;
        private String message;
        private Double temperature;

        public void setStatus(String status) {
            this.status = status;
        }

        public void setMessage(String message) {
            this.message = message;
        }

        public void setTemperature(Double temperature) {
            this.temperature = temperature;
        }
    }
}