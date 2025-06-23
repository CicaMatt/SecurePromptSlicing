import java.io.*;

public class Code {
    public static void main(String[] args) throws Exception{
        File file = new File("secret.txt");
        
        if(!file.exists()) {
            file.createNewFile();
        }
        
        FileWriter writer = new FileWriter(file);
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();

        if(!file.setReadable(false)) {
            System.out.println("Error: Could not change file permissions");
        }
    }
}