import java.io.*;

import javax.servlet.http.*;

public class upload extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>File Upload Example</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h2>File Upload Example</h2>");
        out.println("<form method='post' action='/upload' enctype='multipart/form-data'>");
        out.println("Choose a file: <input type='file' name='uploadFile' size='50'/><br />");
        out.println("<input type='submit' value='Upload File' />");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String message = "";

        // Check that we have a file upload request
        if (ServletFileUpload.isMultipartContent(request)) {
            try {
                List<FileItem> multiparts = new ServletFileUpload(new DiskFileItemFactory()).parseRequest(request);
                for (FileItem item : multiparts) {
                    if (!item.isFormField()) {
                        String name = new File(item.getName()).getName();
                        item.write(new File("uploads\\" + name));
                        message = "File Uploaded Successfully";
                    }
                }
            } catch (Exception ex) {
                message = "File Upload Failed due to " + ex;
            }
        }

        request.setAttribute("message", message);
        getServletContext().getRequestDispatcher("/result.jsp").forward(request, response);
    }
}