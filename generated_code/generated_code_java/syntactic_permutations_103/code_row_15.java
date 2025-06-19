import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Scanner;

public class CreateFile {
    public static void main(String[] args) throws IOException{
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the file name: ");
        String fileName = input.next();

        File file = new File(fileName);
        boolean result = file.createNewFile();
        if (result) {
            System.out.println("File created successfully.");
        } else {
            System.out.println("Error creating the file.");
        }
    }
}