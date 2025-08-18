import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api/temperature_for_location")
public class TemperatureServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");

        if (latitude == null || longitude == null || year == null || month == null || day == null || gribFile == null) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Missing parameters.");
            return;
        }

        double maxTemperature = getMaxTemperature(latitude, longitude, year, month, day, gribFile);

        response.setContentType("application/json");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write("{\"max_temperature\": " + maxTemperature + "}");
    }

    private double getMaxTemperature(String latitude, String longitude, String year, String month, String day, String gribFile) {
        // Dummy implementation for demonstration purposes
        // Replace with actual logic to query the maximum temperature based on provided parameters

        // Simulate a database or external service call here
        return Math.random() * 40; // Random value between 0 and 40 degrees Celsius
    }
}