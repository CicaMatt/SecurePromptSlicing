import java.io.*;
import java.net.*;
import java.sql.*;
import java.util.*;
import com.mysql.jdbc.*;

public class TemperatureAPI {
    private static final String DB_URL = "jdbc:mysql://localhost/mydb";
    private static final String USER = "root";
    private static final String PASS = "password";
    private static final String DRIVER = "com.mysql.jdbc.Driver";
    
    public static void main(String[] args) throws Exception {
        Class.forName(DRIVER);
        Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
        
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new MyHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
    
    static class MyHandler implements HttpHandler {
        
        @Override
        public void handle(HttpExchange t) throws IOException {
            String requestMethod = t.getRequestMethod();
            
            if (requestMethod.equalsIgnoreCase("GET")) {
                Headers responseHeaders = t.getResponseHeaders();
                responseHeaders.set("Content-Type", "application/json");
                
                List<String> queryParams = new ArrayList<>();
                String queryString = t.getRequestURI().getQuery();
                for (String param : queryString.split("&")) {
                    String[] pair = param.split("=");
                    if (pair.length > 1) {
                        queryParams.add(param);
                    }
                }
                
                Map<String, Object> response = new HashMap<>();
                try {
                    PreparedStatement stmt = conn.prepareStatement("SELECT MAX(temperature) FROM temperature_data WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?");
                    
                    // latitude
                    String param = getParam(queryParams, "latitude");
                    stmt.setDouble(1, Double.parseDouble(param));
                    
                    // longitude
                    param = getParam(queryParams, "longitude");
                    stmt.setDouble(2, Double.parseDouble(param));
                    
                    // year
                    param = getParam(queryParams, "year");
                    stmt.setInt(3, Integer.parseInt(param));
                    
                    // month
                    param = getParam(queryParams, "month");
                    stmt.setInt(4, Integer.parseInt(param));
                    
                    // day
                    param = getParam(queryParams, "day");
                    stmt.setInt(5, Integer.parseInt(param));
                    
                    // grib_file
                    param = getParam(queryParams, "grib_file");
                    stmt.setString(6, param);
                    
                    ResultSet rs = stmt.executeQuery();
                    
                    if (rs.next()) {
                        response.put("temperature", rs.getDouble(1));
                    } else {
                        response.put("error", "No data found");
                    }
                } catch (SQLException e) {
                    System.out.println(e);
                    response.put("error", "Query failed");
                }
                
                String jsonResponse = new Gson().toJson(response);
                t.sendResponseHeaders(200, jsonResponse.length());
                OutputStream os = t.getResponseBody();
                os.write(jsonResponse.getBytes());
                os.close();
            } else {
                String response = "Only GET requests are allowed";
                t.sendResponseHeaders(405, response.length());
                OutputStream os = t.getResponseBody();
                os.write(response.getBytes());
                os.close();
            }
        }
        
        private String getParam(List<String> params, String key) {
            for (String param : params) {
                if (param.startsWith(key + "=")) {
                    return param.substring((key + "=").length());
                }
            }
            return null;
        }
    }
}