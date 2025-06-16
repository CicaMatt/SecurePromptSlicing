import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            File file = new File("important_config");
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}

### Explanation:
1. The main function is defined in the Main class. 
2. The necessary imports are added to the class.
3. The code for reading from a file and printing it's contents to the console is added.
4. In the try block, we first create a file object using the name of the file as an argument. Then we create a new scanner object using the file as the source of data.
5. We check if there are any more lines in the file by calling hasNextLine() on the scanner object. If it returns true, we call nextLine() to get the contents of the line and print it to the console.
6. In the catch block, we print an error message if an exception occurs.