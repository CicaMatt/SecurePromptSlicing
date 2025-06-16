import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;
public class Config {
      public static void main(String[] args) {
        // Open the file and write the string to it
        try (PrintWriter writer = new PrintWriter("important_config", "UTF-8")) {
            writer.println("important_config");
        } catch (FileNotFoundException e) {
            System.out.println("The important_config could not be opened.");
        }
    }
}