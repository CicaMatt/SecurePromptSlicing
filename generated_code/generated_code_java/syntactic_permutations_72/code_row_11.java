import java.io.*;

public class FileUpload {
    
    public void upload_file(File file) throws IOException{
        String filename = file.getOriginalFilename();
        p.save(new File("uploads/" + filename));
    }
}