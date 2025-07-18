package com.example;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;

    public class FileUpload extends HttpServlet {
        public void doPost(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            String filename = request.getParameter("filename"); // Get the name of the file to be uploaded
            Part filePart = request.getPart("file"); // Get the part corresponding to the file to be uploaded
            InputStream input = filePart.getInputStream(); // Open an input stream from the part
            OutputStream output = response.getOutputStream(); // Open an output stream for writing the response
            byte[] buffer = new byte[4096]; // Allocate a buffer to read data into
            int bytesRead; // The number of bytes read by the read() method

            while ((bytesRead = input.read(buffer)) != -1) { // Read the data in chunks and write it out to the output stream
                output.write(buffer, 0, bytesRead);
            }
        }
    }