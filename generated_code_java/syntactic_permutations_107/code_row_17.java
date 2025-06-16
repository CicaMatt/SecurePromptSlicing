import java.io.*;

public class SecretFile {
    public static void main(String[] args) throws Exception {
        String secretMessage = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        File myFile = new File("secret.txt");
        if (myFile.createNewFile()) {
            System.out.println("File created: " + myFile.getName());
        } else {
            System.out.println("File already exists.");
        }
        
        Writer writer = new FileWriter(myFile);
        writer.write(secretMessage);
        writer.close();
    }
}