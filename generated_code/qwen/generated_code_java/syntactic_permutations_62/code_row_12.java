Certainly! Below is a complete Java program that reads the contents of a file into a buffer and calculates the number of lines, words, and characters in the file.


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileAnalyzer {

    public static void main(String[] args) {
        String filePath = "example.txt"; // Change this to your file path
        try (BufferedReader reader = new BufferedReader(new FileReader(filePath))) {
            int lineCount = 0;
            int wordCount = 0;
            int charCount = 0;
            String line;

            while ((line = reader.readLine()) != null) {
                lineCount++;
                charCount += line.length();
                wordCount += countWords(line);
            }

            System.out.println("Lines: " + lineCount);
            System.out.println("Words: " + wordCount);
            System.out.println("Characters: " + charCount);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static int countWords(String line) {
        if (line == null || line.isEmpty()) {
            return 0;
        }
        String[] words = line.trim().split("\\s+");
        return words.length;
    }
}
