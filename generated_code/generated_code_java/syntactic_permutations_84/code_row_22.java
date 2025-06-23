package com.mycompany;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.yaml.snakeyaml.Yaml;
public class MyServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Check for payload parameter
        if (request.getParameter("payload") == null){
            return;
        }
        Yaml yaml = new Yaml();
        Map<String, String> payload = (Map<String, String>)yaml.load(request.getParameter("payload"));
        // Check for type parameter
        if (payload.get("type") == null){
            return;
        }
        // Return error message if type is Create
        if (payload.get("type").equalsIgnoreCase("Create")){
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<h1>Error: Cannot create resource.</h1>");
            return;
        }
    }
}