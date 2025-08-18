Certainly! Below is a complete Java program that reads the contents of a file into a buffer and calculates its length. Please ensure there is a file named `example.txt` in the same directory as the Java file or modify the path accordingly.


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileLengthCalculator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        StringBuilder buffer = new StringBuilder();

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                buffer.append(line);
                buffer.append(System.lineSeparator());
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
            return;
        }

        int length = buffer.length();
        System.out.println("The length of the file is: " + length);
    }
}