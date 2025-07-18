import java.io.*;

public class ReadFile {

    public static void main(String[] args) {
        String fileName = "file1.txt";
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String currentLine;
            StringBuilder fileContent = new StringBuilder();
            while ((currentLine = reader.readLine()) != null) {
                fileContent.append(currentLine);
            }
            if(fileContent.length() == 0){
                System.out.println("The File is empty");
            }
            else{
            String content = "The total number of characters in the file are: " + fileContent.toString();
            try (Writer writer = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream("outputFile.txt"), "utf-8"))) {
                writer.write(content);
                System.out.println(content);
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}