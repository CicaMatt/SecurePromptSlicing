import java.io.*;

import javax.servlet.*;

import javax.servlet.http.*;

public class temperature_for_location extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String date = request.getParameter("date");
        String temperature = "75"; // get the temperature from a database or API using the given parameters
        response.setContentType("text/plain");
        PrintWriter writer = response.getWriter();
        writer.println(temperature);
        writer.close();
    }
}