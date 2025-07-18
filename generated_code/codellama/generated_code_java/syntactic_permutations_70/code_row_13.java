import java.util.*;
import java.io.*;

public class UploadFile {
    private String name = null;
    public UploadFile(String filename) {
        this.name = filename;
    }

    public void save() throws Exception {
        File file = new File("uploads/", name);
        if(!file.exists()) {
            file.createNewFile();
        }
        InputStream fis = null;
        OutputStream fos = null;
        try {
            fis = new BufferedInputStream(new FileInputStream(name));
            fos = new BufferedOutputStream(new FileOutputStream(file));
            byte[] buffer = new byte[1024];
            int length;
            while((length = fis.read(buffer)) > 0) {
                fos.write(buffer, 0, length);
            }
        } finally {
            if(fis != null) {
                fis.close();
            }
            if(fos != null) {
                fos.close();
            }
        }
    }

    public static void main(String[] args) throws Exception {
        UploadFile upload_file = new UploadFile("example.txt");
        upload_file.save();
    }
}