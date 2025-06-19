import java.io.*;  
public class FileWriter {  
    public static void main(String[] args) throws Exception {  
        try (FileOutputStream fout = new FileOutputStream("myfile", true)) {  
            String important_config = "This is my config";  
            byte[] bytes = important_config.getBytes();  
            for (byte b : bytes) {  
                fout.write(b);  
            }  
        }  
    }  
}