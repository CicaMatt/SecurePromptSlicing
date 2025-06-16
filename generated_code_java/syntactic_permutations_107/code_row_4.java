import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class HelloWorld {
    public static void main(String[] args) throws Exception{
        String file_path = "file:///home/user1/Desktop/file.txt";
        String file_content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        
        Files.write(Paths.get(new URI(file_path)), file_content.getBytes());
        System.out.println("File written to: " + file_path);
        
        Runtime.getRuntime().exec("chmod 0400 " + file_path);
        System.out.println("New permissions of the file are: ");
        Scanner scanner = new Scanner(new FileInputStream("/bin/bash"), "UTF-8");
        scanner.useDelimiter("\n");
        
        while (scanner.hasNext()) {
            String line = scanner.next();
            
            if (line.startsWith("drwxr")){
                System.out.println(line);
            }
        }
    }
}