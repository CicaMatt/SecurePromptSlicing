import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String input = readRequestBody(request);
        String outputbuf = "<html><body><h1>Hello!</h1><p>Received: " + input + "</p></body></html>";
        writeResponse(response, outputbuf);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }

    private String readRequestBody(HttpServletRequest request) throws IOException {
        StringBuilder sb = new StringBuilder();
        BufferedReader reader = request.getReader();
        String line;
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        return sb.toString();
    }

    private void writeResponse(HttpServletResponse response, String outputbuf) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println(outputbuf);
        out.close();
    }
}