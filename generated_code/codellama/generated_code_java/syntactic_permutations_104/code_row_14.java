import java.io.*; 
public class MyFile { 
    public static void main (String [] args) throws IOException{ 
        FileOutputStream f = new FileOutputStream("/path/to/file", true); 
        String str = "important_config"; 
        byte[] data = str.getBytes(); 
        f.write(data, 0, data.length); 
    } 
}