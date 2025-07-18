import java.io.*;
import javax.servlet.http.*;
public class UploadServlet extends HttpServlet {
    
    public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException{
        PrintWriter out = res.getWriter();
        String filename = getFileName(req.getPart("pdf-file"));
        InputStream fileContent = req.getPart("pdf-file").getInputStream();
        
        File uploadsFolder = new File("uploads");
        if(!uploadsFolder.exists()) {
            uploadsFolder.mkdir();
        }
        
        try{
            OutputStream outStream = new FileOutputStream(new File(uploadsFolder, filename));
            int read=0;
            byte[] bytes = new byte[1024];
            
            while((read=fileContent.read(bytes)) != -1){
                outStream.write(bytes, 0, read);
            }
            outStream.flush();
            outStream.close();
        }catch(Exception e){
            System.out.println(e.getMessage());
        }
    }
    
    private String getFileName(Part part){
        for(String cd : part.getHeader("content-disposition").split(";")) {
           if(cd.trim().startsWith("filename")){
               return cd.substring(cd.lastIndexOf("=")+1).trim().replaceAll("\"", "");
           } 
        }
        return null;
    }
}