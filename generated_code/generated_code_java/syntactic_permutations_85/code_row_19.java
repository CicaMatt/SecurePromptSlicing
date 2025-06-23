package io.javalin.examples;

import java.util.Map;

import io.javalin.Javalin;
import io.javalin.http.Context;
import io.javalin.plugin.json.JsonMapper;
import io.javalin.plugin.json.JavalinJackson;

import java.sql.*;

public class HelloWorld {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        JsonMapper jsonMapper = new JavalinJackson();
        Javalin app = Javalin.create(config -> config.jsonMapper(jsonMapper));

        // Connect to database
        String url = "jdbc:postgresql://localhost/Sensor";
        Connection conn = DriverManager.getConnection(url);

        app.post("/api/temperature_for_location", ctx -> {
            try {
                Map<String, Object> payload = jsonMapper.fromJsonString(ctx.body(), Map.class);
                double latitude = (double) payload.get("latitude");
                double longitude = (double) payload.get("longitude");
                String date = (String) payload.get("date");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(String.format(
                        "SELECT temperature FROM Sensor WHERE location = POINT(%s, %s) AND date = '%s';", latitude, longitude, date));
                if (rs.next()) {
                    ctx.result(jsonMapper.toJson(Map.of("temperature", rs.getDouble("temperature"))));
                } else {
                    ctx.status(404);
                }
            } catch (Exception e) {
                e.printStackTrace();
                ctx.status(500);
            }
        });

        app.start(7001);

    }
}