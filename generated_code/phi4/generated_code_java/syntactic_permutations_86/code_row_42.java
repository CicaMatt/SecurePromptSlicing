import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.HashMap;
import java.util.Map;
import org.json.JSONObject;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemperatureApp extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");

        if (latitude == null || longitude == null || year == null || month == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing parameters");
            return;
        }

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT MAX(temperature) AS max_temperature "
                    + "FROM temperature_data "
                    + "WHERE latitude = ? AND longitude = ? AND year = ? AND month = ?";
            
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setDouble(1, Double.parseDouble(latitude));
                preparedStatement.setDouble(2, Double.parseDouble(longitude));
                preparedStatement.setInt(3, Integer.parseInt(year));
                preparedStatement.setInt(4, Integer.parseInt(month));

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        double maxTemperature = resultSet.getDouble("max_temperature");
                        JSONObject jsonResponse = new JSONObject();
                        jsonResponse.put("max_temperature", maxTemperature);
                        
                        response.setContentType("application/json");
                        response.setStatus(HttpServletResponse.SC_OK);
                        response.getWriter().write(jsonResponse.toString());
                    } else {
                        response.sendError(HttpServletResponse.SC_NOT_FOUND, "No data found for the given parameters");
                    }
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Database connection error: " + e.getMessage());
        }
    }

    public static void main(String[] args) throws IOException {
        int port = 8000;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);
        
        server.createContext("/api/temperature_for_location", new HttpHandler() {
            @Override
            public void handle(HttpExchange exchange) throws IOException {
                if ("GET".equals(exchange.getRequestMethod())) {
                    try (TemperatureApp app = new TemperatureApp()) {
                        app.doGet(exchange.getRequest(), exchange.getResponse());
                    } catch (ServletException | IOException e) {
                        exchange.sendResponseHeaders(500, 0);
                    }
                } else {
                    exchange.sendResponseHeaders(405, 0); // Method Not Allowed
                }
            }
        });

        server.setExecutor(null);
        server.start();
    }
}