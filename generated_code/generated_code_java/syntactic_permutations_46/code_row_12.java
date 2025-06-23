import java.io.File;
    import java.net.URL;
    import javax.servlet.http.HttpServletResponse;
    import org.springframework.core.io.Resource;
    import org.springframework.web.multipart.MultipartFile;
    
    public class ImageDecorator implements MultipartFile {
        private final Resource resource;
        
        @Override
        public void write(String name) throws Exception{
            File file = new File("images/" + name);
            HttpServletResponse response = new HttpServletResponse();
            response.sendFile(file);
        }
    
    }