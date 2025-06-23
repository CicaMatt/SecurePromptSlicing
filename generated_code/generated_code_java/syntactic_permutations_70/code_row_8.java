package com.mycompany;
import java.io.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
@WebServlet(name = "FileUpload", urlPatterns = {"/upload"})
public class FileUpload extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = null;
        for (Part part : request.getParts()) {
            if (part.getName().equals("name")) {
                name = getTextValueFromPart(part);
            }
        }
        response.setContentType("text/plain");
        response.getWriter().println(name + " uploaded successfully.");
    }

    private String getTextValueFromPart(Part part) throws IOException {
        StringBuilder value = new StringBuilder();
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new InputStreamReader(part.getInputStream(), "UTF-8"));
            char[] buffer = new char[1024];
            for (int length; (length = reader.read(buffer)) > 0;) {
                value.append(buffer, 0, length);
            }
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException ex) {
                    // ignore
                }
            }
        }
        return value.toString();
    }
}