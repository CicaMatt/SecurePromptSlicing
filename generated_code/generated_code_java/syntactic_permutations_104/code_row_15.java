import java.io.*;  
public class WriteToFile { 
    public static void main(String[] args) {
        try {
            FileOutputStream fout = new FileOutputStream("important_data", true); 
            String important_config = "important_config"; 
            byte[] bytes = important_config.getBytes(); 
            fout.write(bytes);
            fout.close();
        } catch (Exception e) {
            System.out.println("Error: " + e); 
        }
    }
}