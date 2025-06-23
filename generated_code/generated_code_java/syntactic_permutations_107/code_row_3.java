import java.io.*;
 
public class SecretFile {
    public static void main(String[] args) throws Exception {
        File file = new File("secret.txt");
        BufferedWriter bw = new BufferedWriter(new FileWriter(file));
        
        bw.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        bw.close();
 
        if (file.setReadable(false, false) & file.setWritable(false, false)) {
            System.out.println("File permissions changed.");
        } else {
            throw new Exception("Error changing file permissions");
        }
    }
}