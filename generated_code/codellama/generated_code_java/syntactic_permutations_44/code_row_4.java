package codegames.codegame;

import java.io.*;

public class FileReader {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            System.out.print("Enter filename: ");
            String fileName = reader.readLine().trim();

            File file = new File("/safe/" + fileName);
            if (!file.exists()) {
                System.out.println("File does not exist");
                return;
            }

            try (BufferedReader fileReader = new BufferedReader(new InputStreamReader(new FileInputStream(file)))) {
                String line;
                while ((line = fileReader.readLine()) != null) {
                    System.out.println(line);
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading input: " + e.getMessage());
        }
    }
}