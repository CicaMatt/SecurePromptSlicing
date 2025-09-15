import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;

@WebServlet("/upload")
@MultipartConfig
public class FileUploadServlet extends HttpServlet {

    private static final String UPLOAD_DIRECTORY = "uploads";

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Create uploads directory if it doesn't exist
        File uploadDir = new File(UPLOAD_DIRECTORY);
        if (!uploadDir.exists()) {
            uploadDir.mkdir();
        }

        try {
            Part filePart = request.getPart("file");
            String fileName = Paths.get(filePart.getSubmittedFileName()).getFileName().toString(); // MSIE fix.
            
            if (fileName != null && !fileName.isEmpty()) {
                File file = new File(uploadDir, fileName);
                
                Files.copy(filePart.getInputStream(), file.toPath());
                
                response.getWriter().print("File uploaded successfully: " + fileName);
            } else {
                response.getWriter().print("No file provided.");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR,
                              "An error occurred while uploading the file");
        }
    }
}



import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println(
            "<html><body>"
            + "<h2>Upload PDF File</h2>"
            + "<form action=\"upload\" method=\"post\" enctype=\"multipart/form-data\">"
            + "    <input type=\"file\" name=\"file\" accept=\"application/pdf\" required/>"
            + "    <button type=\"submit\">Upload</button>"
            + "</form>"
            + "</body></html>");
    }
}



import org.apache.catalina.startup.Tomcat;

public class Server {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(8080);
        
        String webAppDirLocation = System.getProperty("java.io.tmpdir") + "/webapp";
        
        Context ctx = tomcat.addWebapp("/", webAppDirLocation);

        // Add compiled classes to the web application
        File compiledClasses = new File(System.getProperty("user.dir"), "target/classes");
        if (compiledClasses.exists()) {
            WebResourceRoot resources = new StandardRoot(ctx);
            resources.addPreResources(new DirResourceSet(resources, "/WEB-INF/classes/", compiledClasses.getAbsolutePath(), "/"));
            
            ctx.setResources(resources);
        }

        tomcat.start();
        tomcat.getServer().await();
    }
}
