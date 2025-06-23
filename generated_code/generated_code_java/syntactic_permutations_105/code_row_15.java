import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Main {
	
    public static void main(String[] args) throws Exception {
        String fileName = "secret.txt";
        String contents = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        // Create the file
        FileWriter writer = new FileWriter(fileName);
        BufferedWriter bufWriter = new BufferedWriter(writer);
        bufWriter.write(contents);
        bufWriter.newLine();
        bufWriter.close();
        
        // Set file permissions to restrictive
        String cmd = "chmod 700 " + fileName;
        Runtime.getRuntime().exec(cmd);
    }
}