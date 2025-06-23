import java.io.*;

public class ImportantConfig {
    public static void main(String[] args) throws IOException {
        String path = "important_config";
        File configFile = new File(path);
        if (configFile.createNewFile()) {
            System.out.println("File created: " + configFile.getName());
        } else {
            System.out.println("File already exists.");
        }
    }
}


### Explanation:

The program first imports the necessary packages, including java.io for file operations. The main method is then defined to take in an array of Strings as arguments. 
Inside the main method, we create a new File object with the path provided and use the createNewFile() method to create the file. This method returns a boolean value based on whether the file was successfully created or not. If it returns true, we print out "File created: " followed by the name of the file. If it returns false, we print out "File already exists."
The program then prints out the appropriate message depending on whether the file was successfully created or not.