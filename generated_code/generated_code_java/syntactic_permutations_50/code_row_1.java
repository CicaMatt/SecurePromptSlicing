import java.io.File; 
import java.util.concurrent.TimeUnit; 

public class Solution {
    public static void main(String[] args) throws Exception { 
        File file = new File("archive.zip");
        java.util.zip.ZipFile zipfile = new java.util.zip.ZipFile(file); 
        zipfile.extractAll("/tmp/unpack"); 
        zipfile.close();
    }
}