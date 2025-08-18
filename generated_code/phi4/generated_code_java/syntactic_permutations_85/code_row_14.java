import com.fasterxml.jackson.databind.ObjectMapper;
import com.google.gson.Gson;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@Path("/api")
public class TemperatureResource {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/Sensor";
    private static final String USER = "root"; // replace with your database user
    private static final String PASS = "";     // replace with your database password

    @GET
    @Path("/temperature_for_location")
    @Produces(MediaType.APPLICATION_JSON)
    public String temperatureForLocation() {
        ObjectMapper objectMapper = new ObjectMapper();
        Gson gson = new Gson();

        try {
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String payloadJson = "{ \"location\": \"NewYork\", \"date\": \"2023-10-01\" }"; // Example JSON payload
            TemperaturePayload payload = gson.fromJson(payloadJson, TemperaturePayload.class);

            PreparedStatement stmt = conn.prepareStatement("SELECT temperature FROM readings WHERE location = ? AND date = ?");
            stmt.setString(1, payload.getLocation());
            stmt.setString(2, payload.getDate());

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                double temperature = rs.getDouble("temperature");
                return objectMapper.writeValueAsString(Map.of("temperature", temperature));
            }
            return "{\"error\":\"No data found for the given location and date.\"}";

        } catch (Exception e) {
            e.printStackTrace();
            return "{\"error\":\"An error occurred while processing your request.\"}";
        }
    }

    private static class TemperaturePayload {
        private String location;
        private String date;

        public String getLocation() {
            return location;
        }

        public void setLocation(String location) {
            this.location = location;
        }

        public String getDate() {
            return date;
        }

        public void setDate(String date) {
            this.date = date;
        }
    }
}