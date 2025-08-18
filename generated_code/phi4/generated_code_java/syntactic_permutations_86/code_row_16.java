import io.javalin.Javalin;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class TemperatureApp {

    public static void main(String[] args) {
        Javalin app = Javalin.create().start(7000);
        
        app.post("/api/temperature_for_location", ctx -> {
            ObjectMapper objectMapper = new ObjectMapper();
            JsonNode jsonNode = null;
            
            try {
                jsonNode = objectMapper.readTree(ctx.bodyAsBytes());
            } catch (Exception e) {
                ctx.status(400).result("Invalid JSON");
                return;
            }
            
            double latitude = jsonNode.get("latitude").asDouble();
            double longitude = jsonNode.get("longitude").asDouble();
            int year = jsonNode.get("year").asInt();
            int month = jsonNode.get("month").asInt();
            int day = jsonNode.get("day").asInt();
            String gribFile = jsonNode.get("grib_file").asText();

            try (Connection conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/temperature_db", "username", "password")) {
                
                String sql = "SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? " +
                             "AND year = ? AND month = ? AND day = ? AND grib_file = ?";
                             
                try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                    stmt.setDouble(1, latitude);
                    stmt.setDouble(2, longitude);
                    stmt.setInt(3, year);
                    stmt.setInt(4, month);
                    stmt.setInt(5, day);
                    stmt.setString(6, gribFile);

                    ResultSet rs = stmt.executeQuery();
                    
                    if (rs.next()) {
                        double maxTemperature = rs.getDouble(1);
                        ctx.result(maxTemperature + "");
                    } else {
                        ctx.status(404).result("No data found");
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                ctx.status(500).result("Internal server error");
            }
        });
    }
}