import java.io.*;
import java.net.*;
import java.sql.*;
 
public class TemperatureAPI {
    public static void main(String[] args) throws Exception {
        HttpServer server = HttpServer.create(new InetSocketAddress(8000), 0);
        server.createContext("/api/temperature_for_location", new TempHandler());
        server.setExecutor(null); // creates a default executor
        server.start();
    }
}
 
class TempHandler implements HttpHandler {
    @Override
    public void handle(HttpExchange t) throws IOException {
        try {
            String requestMethod = t.getRequestMethod();
            if (requestMethod.equalsIgnoreCase("GET")) {
                // get the query params
                URI uri = t.getRequestURI();
                String lat = "";
                String lon = "";
                int year, month, day;
                String grib_file = "unknown";
                try {
                    lat = uri.getQuery().split("&")[0].replace("lat=", "");
                    lon = uri.getQuery().split("&")[1].replace("lon=", "");
                    year = Integer.parseInt(uri.getQuery().split("&")[2].replace("year=", ""));
                    month = Integer.parseInt(uri.getQuery().split("&")[3].replace("month=", ""));
                    day = Integer.parseInt(uri.getQuery().split("&")[4].replace("day=", ""));
                } catch (Exception e) {
                    System.out.println("Unable to parse query params");
                    sendResponse(t, 400, "Bad Request: unable to parse query params");
                    return;
                }
 
                // connect to the mysql database
                String dbUrl = "jdbc:mysql://127.0.0.1/weather";
                Connection conn = DriverManager.getConnection(dbUrl, "root", "password");
                PreparedStatement ps = conn.prepareStatement("SELECT MAX(t) FROM weather WHERE lat = ? AND lon = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?");
                ps.setString(1, lat);
                ps.setString(2, lon);
                ps.setInt(3, year);
                ps.setInt(4, month);
                ps.setInt(5, day);
                ps.setString(6, grib_file);
 
                // execute the query
                ResultSet rs = ps.executeQuery();
 
                // process the results
                String output;
                if (rs.next()) {
                    output = "{\"temp\": " + rs.getDouble(1) + "}";
                } else {
                    output = "{\"error\": \"No temperature found for given location\"}";
                }
 
                // send the response back to the client
                sendResponse(t, 200, output);
            } else {
                sendResponse(t, 405, "Method Not Allowed");
            }
        } catch (Exception e) {
            System.out.println("Error handling request: " + t.getRequestURI());
        }
    }
}
 
void sendResponse(HttpExchange t, int code, String message) throws IOException {
    byte[] response = message.getBytes();
    t.sendResponseHeaders(code, response.length);
    OutputStream os = t.getResponseBody();
    os.write(response);
    os.close();
}